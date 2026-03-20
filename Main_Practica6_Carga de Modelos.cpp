//Practica 6      Marín Alva Yulen Caleb Alher
//20/03/2026    320089756
// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
#include <direct.h> 
#include <filesystem>
#include <iostream>

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

//Para tomar las texturas Marín Alva Yulen Caleb Alher
unsigned int loadTexture(const char* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    // Esto voltea la imagen porque OpenGL lee de abajo hacia arriba
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);

    if (data) {
        GLenum format;
        if (nrComponents == 1) format = GL_RED;
        else if (nrComponents == 3) format = GL_RGB;
        else if (nrComponents == 4) format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Parámetros de repetición y filtrado
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else {
        std::cout << "Error al cargar textura en: " << path << std::endl;
        stbi_image_free(data);
        return 0; 
    }

    return textureID;
}



int main( )
{
    //Mi nombre
    std::cout << "Marin Alva Yulen Caleb Alher" << std::endl;
    

    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Carga de modelos y camara sintetica", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shader/modelLoading.vs", "Shader/modelLoading.frag" );
    
    // Load models Marín Alva Yulen Caleb Alher
    Model dog((char*)"ModelsP6/RedDog/RedDog.obj");
    Model mesa((char*)"ModelsP6/Mesa/Table_Wood_01.fbx");       
    Model cake((char*)"ModelsP6/Cake/VIE_FBX.fbx");
    Model crown((char*)"ModelsP6/Crown/Crown.fbx");
    Model sign((char*)"ModelsP6/Cartel/birthday sign.fbx");
    Model vela((char*)"ModelsP6/Vela/light light.fbx");
    Model partyHat((char*)"ModelsP6/PartyHat/polka_party_hat.fbx");
    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    
  
    //Cargar texturas
    unsigned int texCaKe = loadTexture("ModelsP6/Cake/CAKE3.png");
    unsigned int texVela = loadTexture("ModelsP6/Vela/candler text.png");
    unsigned int texSign = loadTexture("ModelsP6/Cartel/Circles_Solid_Black.png");
    char buffer[FILENAME_MAX];
    if (_getcwd(buffer, FILENAME_MAX)) {
        std::cout << "El programa esta buscando desde: " << buffer << std::endl;
    }

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded models Marín Alva Yulen Caleb Alher
        //RedDog
        glm::mat4 model(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        dog.Draw(shader);

        //Mesa
        glm::mat4 modelMesa = glm::mat4(1.0f);
        modelMesa = glm::translate(modelMesa, glm::vec3(0.0f, -1.0f, 1.5f));
        modelMesa = glm::rotate(modelMesa, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        modelMesa = glm::scale(modelMesa, glm::vec3(0.005f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelMesa));
        mesa.Draw(shader);
        
        //Cake
        glm::mat4 modelCake = glm::mat4(1.0f);
        // Subimos el pastel un poco más que la mesa para que no choquen superficies
        modelCake = glm::translate(modelCake, glm::vec3(0.1f, -0.38f, 1.7f));
        modelCake = glm::scale(modelCake, glm::vec3(0.05f)); // Un poco más pequeño que la mesa
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelCake));
        cake.Draw(shader);
        
        //Vela
        glm::mat4 modelVela = glm::mat4(1.0f);
        // Debe compartir el mismo X y Z que el pastel. Subimos en Y para que quede "arriba".
        modelVela = glm::translate(modelVela, glm::vec3(0.0f, -0.05f, 1.5f));
        modelVela = glm::rotate(modelVela, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        modelVela = glm::scale(modelVela, glm::vec3(0.0008f)); // Escala minúscula para que sea proporcional
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelVela));
        vela.Draw(shader);

        //Cartel 
        glm::mat4 modelSign = glm::mat4(1.0f);
        modelSign = glm::translate(modelSign, glm::vec3(0.0f, 1.0f, -3.0f));
        modelSign = glm::rotate(modelSign, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 1.0f));
        modelSign = glm::scale(modelSign, glm::vec3(0.3f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelSign));
        sign.Draw(shader);

        //GORROS 
        
        //Crown
        glm::mat4 modelCrown = glm::mat4(1.0f);
        modelCrown = glm::translate(modelCrown, glm::vec3(0.0f, 0.7f, 0.2f)); // Ajustado a la altura del perro
        modelCrown = glm::scale(modelCrown, glm::vec3(0.09f, 0.09f, 0.09f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelCrown));
        crown.Draw(shader);

        //PartyHat
        glm::mat4 modelPartyHat = glm::mat4(1.0f);
        modelPartyHat = glm::translate(modelPartyHat, glm::vec3(5.0f, 5.1f, 5.0f));
        modelPartyHat = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelPartyHat));
        partyHat.Draw(shader);

        ////Invitado
        //model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //dog.Draw(shader);

        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

   
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }

 

 
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

