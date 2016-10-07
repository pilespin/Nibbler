
#include <project.hpp>
#include <SDL2/SDL.h>
#include <GL/gl.h>

int main()
{   
    // Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }
 
    // Récupération de la vue principale
    SDL_Window *sdlWin(0);
    sdlWin = SDL_CreateWindow(	"Hello",
    									SDL_WINDOWPOS_CENTERED,
    									SDL_WINDOWPOS_CENTERED,
    									800, 
    									600, 
    									SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
 
    if(sdlWin == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }
 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
 
    SDL_GLContext contexteOpenGL(0);
    contexteOpenGL = SDL_GL_CreateContext(sdlWin);
 
    if(contexteOpenGL == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(sdlWin);
        SDL_Quit();
        return -1;
    }
    // Variables d'évènements
 
    bool end = false;
    SDL_Event evenements;
 
    // Boucle principale
    while(!end)
    {
        // Attente d'un évènement
        SDL_WaitEvent(&evenements);

        // Test de l'évènement : Fermeture de l'application
        if(evenements.window.event == SDL_WINDOWEVENT_CLOSE)
            end = true;


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
		
		// float vertices[] = {-0.5, -0.5,   0.0, 0.5,   0.5, -0.5};
        glClear(GL_COLOR_BUFFER_BIT);

//         GLuint VertexArrayID; 
// glGenVertexArrays(1, &VertexArrayID); 
// glBindVertexArray(VertexArrayID);

// Un tableau de trois vecteurs qui représentent trois sommets
// static const GLfloat g_vertex_buffer_data[] = { 
//    -1.0f, -1.0f, 0.0f, 
//    1.0f, -1.0f, 0.0f, 
//    0.0f,  1.0f, 0.0f, 
// };

// Sélectionnez

// // Ceci identifiera notre tampon de sommets
// GLuint vertexbuffer; 
 
// // Génère un tampon et place l'identifiant dans 'vertexbuffer'
// glGenBuffers(1, &vertexbuffer); 
 
// // Les commandes suivantes vont parler de notre tampon 'vertexbuffer'
// glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); 
 
// // Fournit les sommets à OpenGL.
// glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

// // premier tampon d'attributs : les sommets
// glEnableVertexAttribArray(0); 
// glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer); 
// glVertexAttribPointer( 
//    0,                  // attribut 0. Aucune raison particulière pour 0, mais cela doit correspondre au « layout » dans le shader 
//    3,                  // taille
//    GL_FLOAT,           // type 
//    GL_FALSE,           // normalisé ? 
//    0,                  // nombre d'octets séparant deux sommets dans le tampon
//    (void*)0            // décalage du tableau de tampon
// ); 
 
// // Dessine le triangle ! 
// glDrawArrays(GL_TRIANGLES, 0, 3); // Démarre à partir du sommet 0; 3 sommets au total -> 1 triangle 
 
// glDisableVertexAttribArray(0);


        // // Actualisation de la fenêtre
        // // On remplie puis on active le tableau Vertex Attrib 0
        // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, vertices);
        // glEnableVertexAttribArray(0);
        // // On affiche le triangle
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // // On désactive le tableau Vertex Attrib puisque l'on n'en a plus besoin
        // glDisableVertexAttribArray(0);
        // // glClear(GL_COLOR_BUFFER_BIT);
        // // glBegin(GL_TRIANGLES);
        // // glColor3ub(255,0,0);    glVertex2d(-0.75,-0.75);
        // // glColor3ub(0,255,0);    glVertex2d(0,0.75);
        // // glColor3ub(0,0,255);    glVertex2d(0.75,-0.75);
        // // glEnd();
        // // glFlush();
    
        SDL_GL_SwapWindow(sdlWin);

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

    }

 
    // Destruction du contexte OpenGL, de la vue principale et fin de l'application
    SDL_GL_DeleteContext(contexteOpenGL);
    SDL_DestroyWindow(sdlWin);
    SDL_Quit();
    return 0;
}