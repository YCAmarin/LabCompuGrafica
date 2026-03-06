//Practica 2  Marín Alva Yulen Caleb Alher
//Fecha de entrega: 20/02/2026 Núm de cuenta: 320089756
#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Dibujo de Primitivas en 2D", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    // DEFINICIÓN DE LA FLOR (X, Y, Z,  R, G, B)
    // Coordenadas normalizadas: -1.0 a 1.0
    float vertices[] = {
        // --- TALLO (Verde oscuro) ---
        // Triángulo 1 del tallo
        -0.03f, -1.0f, 0.0f,   0.3f, 0.35f, 0.2f, // Abajo Izq
         0.03f, -1.0f, 0.0f,   0.2f, 0.30f, 0.1f, // Abajo Der
         0.03f, -0.2f, 0.0f,   0.3f, 0.35f, 0.2f, // Arriba Der
         // Triángulo 2 del tallo
         -0.03f, -1.0f, 0.0f,   0.3f, 0.35f, 0.2f, // Abajo Izq
          0.03f, -0.2f, 0.0f,   0.3f, 0.35f, 0.2f, // Arriba Der
         -0.03f, -0.2f, 0.0f,   0.4f, 0.45f, 0.3f, // Arriba Izq

         // --- HOJAS (Verde amarillento / Limón) ---
         // Hoja Izquierda
         -0.03f, -0.2f, 0.0f,   0.4f, 0.5f, 0.2f,  // Base
         -0.4f,  -0.1f, 0.0f,   0.5f, 0.7f, 0.3f,  // Punta exterior
         -0.2f,   0.1f, 0.0f,   0.3f, 0.5f, 0.2f,  // Punta superior

         // Hoja Derecha
         0.03f, -0.2f, 0.0f,   0.4f, 0.5f, 0.2f,  // Base
          0.4f,  -0.1f, 0.0f,   0.5f, 0.7f, 0.3f,  // Punta exterior
          0.2f,   0.1f, 0.0f,   0.3f, 0.5f, 0.2f,  // Punta superior

          //Hoja baja izquierda
          -0.03f, -0.4f, 0.0f,   0.4f, 0.6f, 0.2f,
          -0.25f, -0.5f, 0.0f,   0.5f, 0.7f, 0.3f,
          -0.10f, -0.2f, 0.0f,   0.3f, 0.5f, 0.2f,

          //Hoja baja derecha
           0.03f, -0.4f, 0.0f,   0.4f, 0.6f, 0.2f,
           0.25f, -0.5f, 0.0f,   0.5f, 0.7f, 0.3f,
           0.10f, -0.2f, 0.0f,   0.3f, 0.5f, 0.2f,

           // --- PÉTALOS DE LA FLOR (Rosas y Magentas) ---

           // Pétalo Central (El más grande y brillante)
           -0.15f,  0.0f, 0.0f,   1.0f, 0.4f, 0.7f, // Base Izq
            0.15f,  0.0f, 0.0f,   1.0f, 0.3f, 0.6f, // Base Der
            0.0f,   0.7f, 0.0f,   1.0f, 0.8f, 0.9f, // Punta (Rosa claro)

            // Faceta central (diamante en medio)
             0.0f,   0.0f, 0.0f,   1.0f, 0.6f, 0.8f,
             0.15f,  0.2f, 0.0f,   1.0f, 0.5f, 0.7f,
            -0.15f,  0.2f, 0.0f,   1.0f, 0.5f, 0.7f,

            // Pétalo Izquierdo (Más oscuro)
            -0.15f,  0.0f, 0.0f,   0.8f, 0.2f, 0.5f,
            -0.4f,   0.4f, 0.0f,   0.9f, 0.5f, 0.8f,
            -0.05f,  0.5f, 0.0f,   0.7f, 0.1f, 0.4f,

            // Pétalo Derecho (Más oscuro con variación)
             0.15f,  0.0f, 0.0f,   0.8f, 0.2f, 0.5f,
             0.4f,   0.4f, 0.0f,   0.9f, 0.5f, 0.8f,
             0.05f,  0.5f, 0.0f,   0.7f, 0.1f, 0.4f,

             // Pétalo Trasero Izquierdo (Punta fina)
             -0.2f,   0.2f, 0.0f,   0.9f, 0.5f, 0.8f,
             -0.3f,   0.6f, 0.0f,   1.0f, 0.7f, 0.9f,
             -0.1f,   0.4f, 0.0f,   0.8f, 0.3f, 0.6f,

             // Pétalo Trasero Derecho (Punta fina)
              0.2f,   0.2f, 0.0f,   0.9f, 0.5f, 0.8f,
              0.3f,   0.6f, 0.0f,   1.0f, 0.7f, 0.9f,
              0.1f,   0.4f, 0.0f,   0.8f, 0.3f, 0.6f,
    };

    GLuint VBO, VAO; // Quitamos EBO por simplicidad
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Posición (Location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Color (Location 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Fondo blanco para que resalte la flor (o déjalo negro si prefieres)
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.Use();
        glBindVertexArray(VAO);

        // DIBUJAR TRIANGULOS
        // Calculamos cuántos vértices hay: sizeof(vertices) / sizeof(float) / 6 atributos
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(float) / 6);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


        glPointSize(10);
        glDrawArrays(GL_POINTS,0,1);
        
        //glDrawArrays(GL_LINES,0,4);
        glDrawArrays(GL_LINE_LOOP,0,4);
        
        //glDrawArrays(GL_TRIANGLES,0,3);
        //glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,0);

        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}