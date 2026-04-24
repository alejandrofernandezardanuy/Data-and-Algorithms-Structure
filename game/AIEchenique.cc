#include "Player.hh"

/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */	
#define PLAYER_NAME Echenique1

// DISCLAIMER: The following Demo player is *not* meant to do anything
// sensible. It is provided just to illustrate how to use the API.
// Please use AINull.cc as a template for your player.

struct PLAYER_NAME : public Player
{

	/**
	 * Factory: returns a new instance of this class.
	 * Do not modify this function.
	 */
	static Player *factory()
	{
		return new PLAYER_NAME;
	}

	/**
	 * Types and attributes for your player can be defined here.
	 */

	typedef pair<Pos, Dir> Pos_dir;
	typedef vector<vector<Pos_dir>> Matriz;

	
	bool infectado (Unit u) {
		if (u.damage > 0) return true;
		else return false;
	}

	Dir moverse(Pos p,Unit u)
	{
			//si esta infectado solo se pega
			if(infectado(u)) {
				queue<Pos> Q; 
				Q.push(p); 
				Matriz vis(rows(), vector<Pos_dir>(cols(),{Pos(-1, -1), NONE}));
				vis[p.i][p.j].second = TOP;
				while (not Q.empty()) {
					Pos a = Q.front();
					Q.pop();

					for (int i = 0; i < 4; ++i) {
						Pos s = a + Dir(i);

						Cell ce = cell(s);
						if (ce.type != WALL and vis[s.i][s.j].second == NONE) {
							vis[s.i][s.j] = {a, Dir(i)};
							Q.push(s);
							if (ce.unit_id > 0) {
								Unit uenemiga = unit(ce.unit_id);
								//saber si es mia o no
								if(uenemiga.player != me()) {
									while (vis[s.i][s.j].first != p) s = vis[s.i][s.j].first;//ir hacia ella
									return vis[s.i][s.j].second;
								} 
							}
						}
					}
					
				}
			}
		
			//conquistar otras ciudades o caminos
			queue<Pos> Q; 
			Q.push(p); 
			Matriz vis(rows(), vector<Pos_dir>(cols(),{Pos(-1, -1), NONE}));
			vis[p.i][p.j].second = TOP;
			int it = 0;
			while (not Q.empty()) {
				Pos a = Q.front();
				Q.pop();

				for (int i = 0; i < 4; ++i) {
					Pos s = a + Dir(i);

					Cell ce = cell(s);
					if (ce.type != WALL and vis[s.i][s.j].second == NONE) {
						vis[s.i][s.j] = {a, Dir(i)};
						Q.push(s);
						if(it < 12 and ce.mask and not u.mask and not u.immune) { //si a distancia 2 hay una mascara la cojo si no tengo (12;24)*******
							while (vis[s.i][s.j].first != p) s = vis[s.i][s.j].first;
							return vis[s.i][s.j].second;
						} else if (round() > 10 and it < 24 and ce.unit_id > 0) {//si esta a distancia 3 pega**************************
							Unit uenemiga = unit(ce.unit_id);
							//saber si es mia o no
							if(uenemiga.player != me()) {
								while (vis[s.i][s.j].first != p) s = vis[s.i][s.j].first;
								return vis[s.i][s.j].second;
							}
						}else if(ce.type == CITY and city_owner(ce.city_id) != me()) {//priorizar ciudad
							while (vis[s.i][s.j].first != p) s = vis[s.i][s.j].first;
							return vis[s.i][s.j].second;
						} else if(ce.type == PATH and path_owner(ce.path_id) != me()) {//priorizar path
							while (vis[s.i][s.j].first != p) s = vis[s.i][s.j].first;
							return vis[s.i][s.j].second;
						} else if(round() < 100 and u.id%2 == 0){//conseguir cubitos si estan mas cerca
							queue<Pos> Q; 
							Q.push(p); 
							Matriz vis(rows(), vector<Pos_dir>(cols(),{Pos(-1, -1), NONE}));
							vis[p.i][p.j].second = TOP;
							while (not Q.empty()) {
								Pos a = Q.front();
								Q.pop();

								for (int i = 0; i < 4; ++i) {
									Pos s = a + Dir(i);

									Cell ce = cell(s);
									if (ce.type != WALL and vis[s.i][s.j].second == NONE) {
										vis[s.i][s.j] = {a, Dir(i)};
										Q.push(s);
										if (ce.unit_id > 0) {
											Unit uenemiga = unit(ce.unit_id);
											//saber si es mia o no
											if(uenemiga.player != me()) {
												while (vis[s.i][s.j].first != p) s = vis[s.i][s.j].first;//ir hacia ella
												return vis[s.i][s.j].second;
											}
										}
									}
								}
								
							}
						}
					}
				}
				++it;
			}
			
			return NONE;
			
			
	}


	Dir buscar_ciudad(Pos p,int idc, int& dist, Unit u)
	{
		
			//conquistar la ciudad idc
			queue<pair<Pos, int>> Q; 
			Q.push({p, 0}); 
			Matriz vis(rows(), vector<Pos_dir>(cols(),{Pos(-1, -1), NONE}));
			vis[p.i][p.j].second = TOP;
			int it = 0;
			while (not Q.empty()) {
				Pos a = Q.front().first;
				int d = Q.front().second;
				Q.pop();

				for (int i = 0; i < 4; ++i) {
					Pos s = a + Dir(i);

					Cell ce = cell(s);
					if (ce.type != WALL and ce.type != GRASS and vis[s.i][s.j].second == NONE) {
						vis[s.i][s.j] = {a, Dir(i)};
						Q.push({s, d+1});
						if (it < 12 and ce.unit_id > 0) {//si esta a distancia 3 pega**************
							Unit uenemiga = unit(ce.unit_id);
							//saber si es mia o no
							if(uenemiga.player != me()) {
								while (vis[s.i][s.j].first != p) s = vis[s.i][s.j].first;
								dist = d+1;
								return vis[s.i][s.j].second;
							}
						}else if(ce.type == CITY and ce.city_id == idc) {//priorizar ciudad
							while (vis[s.i][s.j].first != p) s = vis[s.i][s.j].first;
							dist = d;
							return vis[s.i][s.j].second;
						} 
						else if(round() < 100 and u.id%2 == 0){//conseguir cubitos si estan mas cerca****************
							queue<Pos> Q; 
							Q.push(p); 
							Matriz vis(rows(), vector<Pos_dir>(cols(),{Pos(-1, -1), NONE}));
							vis[p.i][p.j].second = TOP;
							while (not Q.empty()) {
								Pos a = Q.front();
								Q.pop();

								for (int i = 0; i < 4; ++i) {
									Pos s = a + Dir(i);

									Cell ce = cell(s);
									if (ce.type != WALL and vis[s.i][s.j].second == NONE) {
										vis[s.i][s.j] = {a, Dir(i)};
										Q.push(s);
										if (ce.unit_id > 0) {
											Unit uenemiga = unit(ce.unit_id);
											//saber si es mia o no
											if(uenemiga.player != me()) {
												while (vis[s.i][s.j].first != p) s = vis[s.i][s.j].first;//ir hacia ella
												return vis[s.i][s.j].second;
											}
										}
									}
								}
								
							}
						}
					}
				}
				++it;
			}
			dist = -1;
			return NONE;
			
			
	}



	

	/**
	 * Play method, invoked once per each round.
	 */
	virtual void play()
	{
		vector<Dir> Direcciones;	// ???




		vector<int> vu = my_units(me());
		int n = vu.size();
		for (int i = 0; i < n; ++i)
		{
			Unit u = unit(vu[i]);//la unidad id
			Pos p = u.pos;//posicion de la unidad
			Dir d;

			Cell c = cell(p);

			if (c.type == PATH and u.id%2 == 0) {//********************************* */
				Path pa = path(c.path_id);
				int c1 = pa.first.first;
				int c2 = pa.first.second;

				bool c1_mia = (city_owner(c1) == me());
				bool c2_mia = (city_owner(c2) == me());
				Dir dc1 = NONE;
				Dir dc2 = NONE;
				int distc1, distc2;
				if (not c1_mia) dc1 = buscar_ciudad(p, c1, distc1,u);
				if (not c2_mia) dc2 = buscar_ciudad(p, c2, distc2,u);

				if (not c1_mia and not c2_mia) {
					if (distc1 < distc2) d = dc1;
					else d = dc2;
				}
				else if (not c1_mia) d = dc1;
				else if (not c2_mia) d = dc2;
				else d = moverse(p, u);

			}
			else {
				d = moverse(p,u);//direccion a la que se mueve
			}

			move(vu[i], d);//moverse
		}
	}
};

/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
