#include "Classes/field.h"
#include "Classes/cell.h"
#include "Classes/waterCell.h"
#include "Classes/movingWallCell.h"
#include "Classes/staticWallCell.h"
#include "Settings/params.h"

#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <memory>
#include <cmath>
#include <cassert>      // для assert
#include <iostream>     // для std::cerr
#include <exception>    // для std::exception


extern "C" {


Field* initialize_field() {
    Field * field = new Field(XGridSize,YGridSize);
    std::ifstream file(FileName);
    if (!file.is_open()) {
        delete field;
        return NULL; //throw std::runtime_error("Failed to open file: " + std::string(FileName));
    }
    for (int y = 0; y < YGridSize; y++) {
        for (int x = 0; x < XGridSize; x++) {
            char c = file.get();
            if (file.eof()) {
                break;
            }
            if (!file) {
                delete field;
                return NULL;
                //throw std::runtime_error("Failed to read file: " + std::string(FileName) + " or file is wrong");
            }
            switch (c) {
                case 's': field->set_cell(x, y, std::make_unique<StaticWallCell>(x, y)); break;
                case 'm': field->set_cell(x, y, std::make_unique<MovingWallCell>(x, y, 1, 1)); break;
                case 'M': field->set_cell(x, y, std::make_unique<MovingWallCell>(x, y, 1, 0)); break;
                case 'w': field->set_cell(x, y, std::make_unique<WaterCell>(x, y, 0, 0, 0));  break;
                case '\n': x--; break;
                default: delete field; return NULL; //throw std::runtime_error("Invalid character in file: " + std::string(FileName));
            }
        }
    }
    return field;
    }


    
    int get_x(Cell* cell) {
        return cell->get_x();
    }

    int get_y(Cell* cell) {
        return cell->get_y();
    }

    const char* get_type(Cell* cell) {
        return cell->get_type().c_str();
    }
    


    Field* create_field(int xSize, int ySize) {
            
        if (xSize <= 0 || ySize <= 0) {
            throw std::invalid_argument("Field dimensions must be positive integers");
        }

        Field* field = new Field(xSize, ySize);

        field->set_xSize(xSize);
        field->set_ySize(ySize);
        for (int x = 0; x < xSize; x++) {
            for (int y = 0; y < ySize; y++) {
                field->set_cell(x, y, std::make_unique<Cell>(x, y));
            }
        }

        return field;
    }

    Cell* get_cell(Field* field, int x, int y) {
        return field->get_cell(x, y);
    }


    void display(Field* field) {
        for (int i = 0; i < 4 * field->get_xSize() + 1; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;

        for (int y = 0; y < field->get_ySize(); y++) {
            std::cout << "|";
            for (int x = 0; x < field->get_xSize(); x++) {
                std::cout << " " << field->get_cell(x, y)->get_description() << " |";
            }
            std::cout << std::endl;

            for (int i = 0; i < 4 * field->get_xSize() + 1; i++) {
                std::cout << "-";
            }
            std::cout << std::endl;
        }
    }

    void display_without_walls(Field* field) {
        for (int y = 0; y < field->get_ySize(); y++) {
            for (int x = 0; x < field->get_xSize(); x++) {
                std::cout << field->get_cell(x, y)->get_description();
            }
            std::cout << std::endl;
        }
    }


    void display_test(Field* field) {
        for (int y = 0; y < field->get_ySize(); y++) {
            for (int x = 0; x < field->get_xSize(); x++) {
                std::cout << "| " << field->get_cell(x, y)->get_description_test() << " ";
            }
            std::cout << "|" << std::endl;
        }
    }


    float get_u(WaterCell* cell) {
        return cell->get_u();
    }

    float get_v(WaterCell* cell) {
        return cell->get_v();
    }

    float get_p(WaterCell* cell) {
        return cell->get_p();
    }



    void update(Field* field) {
        assert(field && "update: Field pointer is null");
        const int NX = field->get_xSize();
        const int NY = field->get_ySize();
        if (NX <= 2 || NY <= 2) {
            std::cerr << "update: Grid too small (NX=" << NX << ", NY=" << NY << ")\n";
            return;
        }
    
        // 1) Advection + diffusion (WaterCell)
        std::vector<std::vector<float>> u_star(NX, std::vector<float>(NY, 0.0f));
        std::vector<std::vector<float>> v_star(NX, std::vector<float>(NY, 0.0f));
        std::vector<std::vector<float>> p_new  (NX, std::vector<float>(NY, 0.0f));
    
        auto fetch_u = [&](int i, int j) {
            if (i<0||i>=NX||j<0||j>=NY) return 0.0f;
            Cell* c = field->get_cell(i, j);
            if      (c->get_type() == "Water")      return static_cast<WaterCell*>(c)->get_u();
            else if (c->get_type() == "MovingWall") return static_cast<MovingWallCell*>(c)->get_u();
            else                                     return 0.0f;
        };
        auto fetch_v = [&](int i, int j) {
            if (i<0||i>=NX||j<0||j>=NY) return 0.0f;
            Cell* c = field->get_cell(i, j);
            if      (c->get_type() == "Water")      return static_cast<WaterCell*>(c)->get_v();
            else if (c->get_type() == "MovingWall") return static_cast<MovingWallCell*>(c)->get_v();
            else                                     return 0.0f;
        };
    
        for (int i = 1; i < NX-1; ++i) {
            for (int j = 1; j < NY-1; ++j) {
                Cell* base = field->get_cell(i, j);
                if (!base || base->get_type() != "Water") continue;
                auto* wc = static_cast<WaterCell*>(base);
    
                float u = wc->get_u(), v = wc->get_v();
                float u_ip = fetch_u(i+1,j), u_im = fetch_u(i-1,j);
                float u_jp = fetch_u(i,j+1), u_jm = fetch_u(i,j-1);
                float v_ip = fetch_v(i+1,j), v_im = fetch_v(i-1,j);
                float v_jp = fetch_v(i,j+1), v_jm = fetch_v(i,j-1);
    
                float du_dx = (u_ip - u_im) / (2*DX);
                float du_dy = (u_jp - u_jm) / (2*DY);
                float dv_dx = (v_ip - v_im) / (2*DX);
                float dv_dy = (v_jp - v_jm) / (2*DY);
    
                float d2u = (u_ip - 2*u + u_im)/(DX*DX) + (u_jp - 2*u + u_jm)/(DY*DY);
                float d2v = (v_ip - 2*v + v_im)/(DX*DX) + (v_jp - 2*v + v_jm)/(DY*DY);
    
                u_star[i][j] = u + DT * ( -u*du_dx - v*du_dy + NU * d2u );
                v_star[i][j] = v + DT * ( -u*dv_dx - v*dv_dy + NU * d2v );
            }
        }
    
        // 2) Pressure Poisson (Jacobi)
        for (int iter = 0; iter < PRESSURE_ITERS; ++iter) {
            for (int i = 1; i < NX-1; ++i) {
                for (int j = 1; j < NY-1; ++j) {
                    Cell* c = field->get_cell(i, j);
                    if (!c || c->get_type() != "Water") continue;
                    float rhs = (RHO/DT) * (
                        (u_star[i+1][j] - u_star[i-1][j])/(2*DX)
                      + (v_star[i][j+1] - v_star[i][j-1])/(2*DY)
                    );
                    p_new[i][j] = (
                        (p_new[i+1][j] + p_new[i-1][j]) * DY*DY
                      + (p_new[i][j+1] + p_new[i][j-1]) * DX*DX
                      - rhs * DX*DX * DY*DY
                    ) / (2*(DX*DX + DY*DY));
                }
            }
        }
    
        // 3) Velocity correction
        for (int i = 1; i < NX-1; ++i) {
            for (int j = 1; j < NY-1; ++j) {
                Cell* base = field->get_cell(i, j);
                if (!base || base->get_type() != "Water") continue;
                auto* wc = static_cast<WaterCell*>(base);
    
                float dp_dx = (p_new[i+1][j] - p_new[i-1][j]) / (2*DX);
                float dp_dy = (p_new[i][j+1] - p_new[i][j-1]) / (2*DY);
    
                float u_corr = u_star[i][j] - (DT/RHO) * dp_dx;
                float v_corr = v_star[i][j] - (DT/RHO) * dp_dy;
                float p_val  = p_new[i][j];
                if (!std::isfinite(p_val) || p_val < 0.0f) {
                    p_val = 0.0f;
                }
    
                wc->set_u(u_corr);
                wc->set_v(v_corr);
                wc->set_p(p_val);
            }
        }
    
        // 3.5) CONSTANT flow on MovingWall (left & right)
        {
            const float Uwall = 1000;  // в params.h задайте это как желаемую постоянную скорость
            for (int j = 1; j < NY-1; ++j) {
                if (auto* cL = field->get_cell(0, j); cL && cL->get_type() == "MovingWall") {
                    auto* mwL = static_cast<MovingWallCell*>(cL);
                    mwL->set_u(Uwall);    // постоянная горизонтальная скорость
                    mwL->set_v(0.0f);     // вертикальная составляющая занулена
                }
                if (auto* cR = field->get_cell(NX-1, j); cR && cR->get_type() == "MovingWall") {
                    auto* mwR = static_cast<MovingWallCell*>(cR);
                    mwR->set_u(Uwall);
                    mwR->set_v(0.0f);
                }
            }
        }
    
        // 3.6) No-slip for StaticWall
        {
            const int di[4] = { -1, +1,  0,  0 };
            const int dj[4] = {  0,  0, -1, +1 };
            for (int i = 0; i < NX; ++i) {
                for (int j = 0; j < NY; ++j) {
                    auto* c = field->get_cell(i, j);
                    if (!c || c->get_type() != "StaticWall") continue;
                    for (int k = 0; k < 4; ++k) {
                        int ni = i + di[k], nj = j + dj[k];
                        if (ni<0||ni>=NX||nj<0||nj>=NY) continue;
                        if (auto* nb = field->get_cell(ni, nj); nb && nb->get_type() == "Water") {
                            auto* wc = static_cast<WaterCell*>(nb);
                            wc->set_u(0.0f);
                            wc->set_v(0.0f);
                        }
                    }
                }
            }
        }
    
        // 4) Single impulse from any MovingWallCell
        for (int i = 0; i < NX; ++i) {
            for (int j = 0; j < NY; ++j) {
                Cell* base = field->get_cell(i, j);
                if (!base || base->get_type() != "MovingWall") continue;
                auto* mw = static_cast<MovingWallCell*>(base);
                float mu = mw->get_u(), mv = mw->get_v();
                if (mu == 0.0f && mv == 0.0f) continue;
                int diw = (mu > 0 ? +1 : (mu < 0 ? -1 : 0));
                int djw = (mv > 0 ? +1 : (mv < 0 ? -1 : 0));
                int ni = i + diw, nj = j + djw;
                if (ni>=0&&ni<NX&&nj>=0&&nj<NY) {
                    if (auto* nb = field->get_cell(ni, nj); nb && nb->get_type() == "Water") {
                        auto* wc = static_cast<WaterCell*>(nb);
                        wc->set_u(wc->get_u() + mu);
                        wc->set_v(wc->get_v() + mv);
                    }
                }
                mw->set_u(0.0f);
                mw->set_v(0.0f);
            }
        }
    }
}