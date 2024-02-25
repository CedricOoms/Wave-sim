#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <cstdlib>

GLFWwindow* window;

struct Dot{
    float pos[2];
    float vel[2];
    void position(float x, float y){
        pos[0] = x;
        pos[1] = y;
    }
    void velocity(float v_x, float v_y){
        vel[0] = v_x;
        vel[1] = v_y;
    }
    void updatePosition(){
        float dt = 0.1f;
        pos[0] = pos[0] + dt * vel[0];
        pos[1] = pos[1] + dt * vel[1];
        if (pos[0] < -1 || pos[0] > 1){
            vel[0] = - vel[0];
        }
        if (pos[1] < -1 || pos[1] > 1){
            vel[1] = - vel[1];
        }
    }
};

void setupBuffer(unsigned int vbo){
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

}

void draw(float data[2]){
    glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float), data, GL_DYNAMIC_DRAW);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_POINTS, 0, 2);
    glfwSwapBuffers(window);
}

void render(){
    Dot dot;
    dot.position(0.0f, 0.0f);
    dot.velocity(0.01f, 0.05f);
    dot.updatePosition();
    draw(dot.pos);
}

int main(){

    if (!glfwInit()){
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Test", NULL, NULL);

    if (!window){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    unsigned int buffer;
    setupBuffer(buffer);


    while (!glfwWindowShouldClose(window)){
        render();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}