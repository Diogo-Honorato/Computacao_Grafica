#include "../include/Clipping.hpp"

Clipping::Clipping(float xmin,float ymin,float xmax,float ymax):x_min(xmin),y_min(ymin),x_max(xmax),y_max(ymax)
{
    
    sh = new Shader(DEFAULT_LINE_VERTEX,DEFAULT_LINE_FRAGMENT);
    tsh = new Shader("../shader/shaders_clipping/CS_square.vs","../shader/shaders_clipping/CS_square.fs");
    Mesh *telaMesh = Mesh::squareMesh(false,false);
    tela = new Shape(telaMesh,tsh);
    telaMesh->clearCPUData();
    if(telaMesh)delete telaMesh;
}

Clipping::~Clipping(){
    if(tela) delete tela;
    if(sh) delete sh;
    if(tsh) delete tsh;
}

void Clipping::generateRandomLines() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(x_min - 0.5f, x_max + 0.5f);
    std::uniform_real_distribution<float> distY(y_min - 0.5f, y_max + 0.5f);
    originalLines.clear();
    clippedLines.clear();
    
    for (int i = 0; i < 10; ++i) {
        float x1 = distX(gen);
        float y1 = distY(gen);
        float x2 = distX(gen);
        float y2 = distY(gen);

        std::vector<float> points = {x1, y1, 0.0f, x2, y2, 0.0f};
        std::vector<GLuint> indices = {0, 1};

        try {
            Mesh *line = Mesh::lineMesh(points,indices);
            originalLines.push_back(std::make_unique<Shape>(line,sh));
            line->clearCPUData();
            if(line)delete line;

            clipLine(x1, y1, x2, y2);
        } catch (const std::exception &e) {
            std::cerr << "Erro ao criar linha: " << e.what() << std::endl;
        }
    }
}

void Clipping::draw() {
    tela->getShader()->useShaders();
    tela->desenharElem();

    // Desenha linhas originais (vermelhas)
    for (size_t i = 0; i < originalLines.size(); ++i) {
        
        originalLines[i]->getShader()->useShaders();
        originalLines[i]->getShader()->setVec3("lineColor", outsideColor);
        originalLines[i]->desenharLine();
    }

    // Desenha linhas recortadas (azuis)
    for (size_t i = 0; i < clippedLines.size(); ++i) {
        clippedLines[i]->getShader()->useShaders();
        clippedLines[i]->getShader()->setVec3("lineColor", insideColor);
        clippedLines[i]->desenharLine();
    }
}

int Clipping::computeCode(float x, float y) {
    int code = INSIDE;

    if (x < x_min) code |= LEFT_SIDE;
    else if (x > x_max) code |= RIGHT_SIDE;
    if (y < y_min) code |= BOTTOM;
    else if (y > y_max) code |= TOP;

    return code;
}

void Clipping::clipLine(float x1, float y1, float x2, float y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;
    
    while (true) {
        if (!(code1 | code2)) {
            accept = true;
            break;
        } else if (code1 & code2) {
            break;
        } else {
            float x, y;
            int codeOut = code1 ? code1 : code2;

            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            } else if (codeOut & RIGHT_SIDE) {
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            } else if (codeOut & LEFT_SIDE) {
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        std::vector<float> points = {x1, y1, 0.0f, x2, y2, 0.0f};
        std::vector<GLuint> indices = {0, 1};

        try {
            
            Mesh *line = Mesh::lineMesh(points,indices);
            clippedLines.push_back(std::make_unique<Shape>(line,sh));
            line->clearCPUData();
            if(line)delete line;
            
        } catch (const std::exception &e) {
            std::cerr << "Erro ao criar linha recortada: " << e.what() << std::endl;
        }
    }
}
