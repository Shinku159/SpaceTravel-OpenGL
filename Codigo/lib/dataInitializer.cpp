#include "dataInitializer.h"

void initStarsData (unsigned int VAO[], unsigned int VBO[], float color[], float size[], int starNumber){
    int i;
    float stars[starNumber][3];
    for (i = 0; i < starNumber; i++){
        //primeiro vertice (0.0)
        color[i] = ((float)rand()/(float)(RAND_MAX));
        size[i] = (rand() % 3) + 2;
        stars[i][0] =  (((float)rand()/(float)(RAND_MAX)) * 38) - 19;
        stars[i][1] = (((float)rand()/(float)(RAND_MAX)) * 38) - 19;
        stars[i][2] = -10.0f;
    }
    
    // Vertex array.
    glGenVertexArrays(starNumber, VAO);
    glGenBuffers(starNumber, VBO);
    
    for (i = 0; i < starNumber; i++){
        glBindVertexArray(VAO[i]);

        // Vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(stars[i]), stars[i], GL_STATIC_DRAW);
        
        // Set attributes.
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind Vertex Array Object.
        glBindVertexArray(0);
    } 
}

void initSpaceShip (unsigned int *VAO, unsigned int *VBO, int color){
    float R, G, B;
    switch(color){
        case 0: //Pink
            R = 1.0;
            G = 0.5;
            B = 1.0;
            break;
        case 1: //Ciano
            R = 0.5;
            G = 1.0;
            B = 1.0;
            break;
        case 2: //Green
            R = 0.5;
            G = 1.0;
            B = 0.5;
            break;
        case 3: //Yellow
            R = 1.0;
            G = 1.0;
            B = 0.5;
            break;
        case 4: //Orange
            R = 1.0;
            G = 0.5;
            B = 0.5;
            break;
    }
    

    float starShip[] = {
        //Front face first triangle.
        // coordinate        // color
         0.0f,  1.0f,  0.0f, (R-0.3f), (G-0.3f), (B-0.3f),
        -1.0f, -1.0f,  0.0f, (R-0.3f), (G-0.3f), (B-0.3f),
         1.0f, -1.0f,  0.0f, (R-0.3f), (G-0.3f), (B-0.3f),
        // Right face
         1.0f, -1.0f,  0.0f, R, G, B,
         0.0f,  1.0f,  0.0f, R, G, B,
         0.0f, -1.0f, -1.0f, R, G, B,
        // Left face
        -1.0f, -1.0f,  0.0f, (R-0.1f), (G-0.1f), (B-0.1f),
         0.0f,  1.0f,  0.0f, (R-0.1f), (G-0.1f), (B-0.1f),
         0.0f, -1.0f, -1.0f, (R-0.1f), (G-0.1f), (B-0.1f),
        // Bottom face
        -1.0f, -1.0f,  0.0f, 0.5, 0.0, 0.0,
         1.0f, -1.0f,  0.0f, 0.5, 0.0, 0.0,
         0.0f, -1.0f, -1.0f, 0.5, 0.0, 0.0
    };

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    // Vertex array.
    glBindVertexArray(*VAO);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(starShip), starShip, GL_STATIC_DRAW);
    
    // Set attributes.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind Vertex Array Object.
    glBindVertexArray(0);
}

void initPlanet(unsigned int *VAO, unsigned int *VBO, float positions[], float x, float y, float R, float G, float B, float size){
    float sizei = size * -1;

    positions[0]=x;    
    positions[1]=y;
    positions[2]=(float) (rand() % 360);    
    positions[3]=(float) (rand() % 360);
    positions[4]=(float) (rand() % 360);    
    float planet[] ={
        //FIRST SIDE
        //coord     //color  //normal
        sizei, size, size, R, G, B, 0.0, 0.0, 1.0,
        sizei, sizei, size, R, G, B, 0.0, 0.0, 1.0,
        size, sizei, size, R, G, B, 0.0, 0.0, 1.0,

        size, sizei, size, R, G, B, 0.0, 0.0, 1.0,
        size, size, size, R, G, B, 0.0, 0.0, 1.0,
        sizei, size, size, R, G, B, 0.0, 0.0, 1.0,

        //SECOND SIDE
        sizei, size, sizei, R, G, B, 0.0, 0.0, -1.0,
        sizei, sizei, sizei, R, G, B, 0.0, 0.0, -1.0,
        size, sizei, sizei, R, G, B, 0.0, 0.0, -1.0,

        size, sizei, sizei, R, G, B, 0.0, 0.0, -1.0,
        size, size, sizei, R, G, B, 0.0, 0.0, -1.0,
        sizei, size, sizei, R, G, B, 0.0, 0.0, -1.0,

        //THIRD SIDE
        sizei, size, size, R, G, B, 0.0, 1.0, 0.0,
        size, size, sizei, R, G, B, 0.0, 1.0, 0.0,
        sizei, size, sizei, R, G, B, 0.0, 1.0, 0.0,

        sizei, size, size, R, G, B, 0.0, 1.0, 0.0,
        size, size, size, R, G, B, 0.0, 1.0, 0.0,
        size, size, sizei, R, G, B, 0.0, 1.0, 0.0,

        //FORTH SIDE
        sizei, sizei, size, R, G, B, 0.0, -1.0, 0.0,
        size, sizei, sizei, R, G, B, 0.0, -1.0, 0.0,
        sizei, sizei, sizei, R, G, B, 0.0, -1.0, 0.0,

        sizei, sizei, size, R, G, B, 0.0, -1.0, 0.0,
        size, sizei, size, R, G, B, 0.0, -1.0, 0.0,
        size, sizei, sizei, R, G, B, 0.0, -1.0, 0.0,

        //FIFTH SIDE
        sizei, size, size, R, G, B, -1.0, 0.0, 0.0,
        sizei, sizei, size, R, G, B, -1.0, 0.0, 0.0,
        sizei, sizei, sizei, R, G, B, -1.0, 0.0, 0.0,

        sizei, size, size, R, G, B, -1.0, 0.0, 0.0,
        sizei, sizei, sizei, R, G, B, -1.0, 0.0, 0.0,
        sizei, size, sizei, R, G, B, -1.0, 0.0, 0.0,

        //SIXTH SIDE
        size, size, size, R, G, B, 1.0, 0.0, 0.0,
        size, sizei, size, R, G, B, 1.0, 0.0, 0.0,
        size, sizei, sizei, R, G, B, 1.0, 0.0, 0.0,

        size, size, size, R, G, B, 1.0, 0.0, 0.0,
        size, sizei, sizei, R, G, B, 1.0, 0.0, 0.0,
        size, size, sizei, R, G, B, 1.0, 0.0, 0.0,
    };

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    // Vertex array.
    glBindVertexArray(*VAO);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planet), planet, GL_STATIC_DRAW);
    
    // Set attributes.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind Vertex Array Object.
    glBindVertexArray(0);
}

void initSpherePlanet(unsigned int *VAO, unsigned int *VBO, float positions[], float x, float y, float R, float G, float B, float size, int *vertices){
    float sizei = size * -1;

    std::vector < glm::vec3 > out_vertices; //vertices
    std::vector < glm::vec2 > out_uvs; // Texture
    std::vector < glm::vec3 > out_normals; //Normal

    positions[0]=x;    
    positions[1]=y;
    positions[2]=size;
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;

    //File with sphere vertices
    FILE * file = fopen("circle.obj", "r");
    if( file == NULL ){
        printf("Impossible to open the file !\n");
        return;
    }

    //READ FILE =================
    while( 1 ){
    char lineHeader[128];
    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
        break; // EOF = End Of File. Quit the loop.

    if ( strcmp( lineHeader, "v" ) == 0 ){
        glm::vec3 vertex;
        fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
        temp_vertices.push_back(vertex);
    }else if ( strcmp( lineHeader, "vt" ) == 0 ){
        glm::vec2 uv;
        fscanf(file, "%f %f\n", &uv.x, &uv.y );
        temp_uvs.push_back(uv);
    }else if ( strcmp( lineHeader, "vn" ) == 0 ){
        glm::vec3 normal;
        fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
        temp_normals.push_back(normal);
    }else if ( strcmp( lineHeader, "f" ) == 0 ){
        std::string vertex1, vertex2, vertex3;
        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
        int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
        if (matches != 9){
            printf("File can't be read by our simple parser : ( Try exporting with other options\n");
            return;
        }
        vertexIndices.push_back(vertexIndex[0]);
        vertexIndices.push_back(vertexIndex[1]);
        vertexIndices.push_back(vertexIndex[2]);
        uvIndices    .push_back(uvIndex[0]);
        uvIndices    .push_back(uvIndex[1]);
        uvIndices    .push_back(uvIndex[2]);
        normalIndices.push_back(normalIndex[0]);
        normalIndices.push_back(normalIndex[1]);
        normalIndices.push_back(normalIndex[2]);
    }}

    //Makes Vertices Array
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
        out_vertices.push_back(vertex);
    }

    //Makes Texture Array
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        unsigned int uvIndex = uvIndices[i];
        glm::vec2 uv = temp_vertices[ uvIndex-1 ];
        out_uvs.push_back(uv);
    }

    //Makes Normal Array
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        unsigned int normalIndex = normalIndices[i];
        glm::vec3 normal = temp_vertices[ normalIndex-1 ];
        out_normals.push_back(normal);
    }
    // ==================================

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    //Creates the planet
    *vertices = vertexIndices.size();
    float cor;
    float planet[vertexIndices.size()][9];
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        planet[i][0] = out_vertices.at(i).x;
        planet[i][1] = out_vertices.at(i).y;
        planet[i][2] = out_vertices.at(i).z;

        planet[i][3] = R;
        planet[i][4] = G;
        planet[i][5] = B;

        planet[i][6] = out_normals.at(i).x;
        planet[i][7] = out_normals.at(i).y;
        planet[i][8] = out_normals.at(i).z;
    }

    // Vertex array.
    glBindVertexArray(*VAO);

   // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planet), planet, GL_STATIC_DRAW);
    
    // Set attributes.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind Vertex Array Object.
    glBindVertexArray(0);
}

void initPyramidPlanet(unsigned int *VAO, unsigned int *VBO, float positions[], float x, float y, float R, float G, float B, float size){
    float sizei = size * -1;

    positions[0]=x;    
    positions[1]=y;
    positions[2]=(float) (rand() % 360);    
    positions[3]=(float) (rand() % 360);
    positions[4]=(float) (rand() % 360);    
    float planet[] ={
        //Right face
        // coordinate        //color  //normal
         size, sizei,  0.0f, R, G, B, 0.5f, 0.5f, 0.5f,
         0.0f,  size,  0.0f, R, G, B, 0.5f, 0.5f, 0.5f,
         0.0f, sizei,  size, R, G, B, 0.5f, 0.5f, 0.5f,
        // Right face2
         size, sizei,  0.0f, R, G, B, 0.5f, 0.5f, -0.5f,
         0.0f,  size,  0.0f, R, G, B, 0.5f, 0.5f, -0.5f, 
         0.0f, sizei, sizei, R, G, B, 0.5f, 0.5f, -0.5f, 
        // Left face
        sizei, sizei,  0.0f, R, G, B, -0.5f, 0.5f, 0.5f, 
         0.0f,  size,  0.0f, R, G, B, -0.5f, 0.5f, 0.5f, 
         0.0f, sizei,  size, R, G, B, -0.5f, 0.5f, 0.5f, 
        // Left face2
        sizei, sizei,  0.0f, R, G, B, -0.5f, 0.5f, -0.5f,
         0.0f,  size,  0.0f, R, G, B, -0.5f, 0.5f, -0.5f, 
         0.0f, sizei, sizei, R, G, B, -0.5f, 0.5f, -0.5f, 
        // Bottom face
        sizei, sizei,  0.0f, R, G, B,  0.0f, -1.0f, 0.0f,
         size, sizei,  0.0f, R, G, B,  0.0f, -1.0f, 0.0f,
         0.0f, sizei, sizei, R, G, B,  0.0f, -1.0f, 0.0f,
        // Bottom face2
        sizei, sizei,  0.0f, R, G, B,  0.0f, -1.0f, 0.0f,
         size, sizei,  0.0f, R, G, B,  0.0f, -1.0f, 0.0f,
         0.0f, sizei,  size, R, G, B,  0.0f, -1.0f, 0.0f,
    };

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    // Vertex array.
    glBindVertexArray(*VAO);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planet), planet, GL_STATIC_DRAW);
    
    // Set attributes.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind Vertex Array Object.
    glBindVertexArray(0);
}
