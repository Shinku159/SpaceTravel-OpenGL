#include "utils.h"

/* === Vertex shader. === */
const char *vertex_code = "\n"
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"layout (location = 2) in vec3 normal;\n"
"\n"
"out vec3 vColor;\n"
"out vec3 vNormal;\n"
"out vec3 fragPosition;\n"
"\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = projection * view * model * vec4(position, 1.0);\n"
"    vNormal = normal;\n"
"    vColor = color;\n"
"    fragPosition = vec3(model * vec4(position, 1.0));\n"
"}\0";

/* === Fragment shader - Color Vector === */
const char *fragment_code = "\n"
"#version 330 core\n"
"\n"
"in vec3 vColor;\n"
"in vec3 vNormal;\n"
"in vec3 fragPosition;\n"
"\n"
"out vec4 FragColor;\n"
"\n"
"uniform vec3 lightColor;\n"
"uniform vec3 lightPosition;\n"
"uniform vec3 cameraPosition;\n"
"uniform vec3 color;\n"
"uniform bool hasColor;\n"
"uniform bool hasLight;\n"
"void main()\n"
"{\n"
"    vec3 lightC, lightV;\n"
"    if(hasLight == true){\n"
"    float ka = 0.5;\n"
"    vec3 ambient = ka * lightColor;\n"
"\n"
"    float kd = 0.8;\n"
"    vec3 n = normalize(vNormal);\n"
"    vec3 l = normalize(lightPosition - fragPosition);\n"
"\n"
"    float diff = max(dot(n,l), 0.0);\n"
"    vec3 diffuse = kd * diff * lightColor;\n"
"\n"
"    float ks = 1.0;\n"
"    vec3 v = normalize(cameraPosition - fragPosition);\n"
"    vec3 r = reflect(-l, n);\n"
"\n"
"    float spec = pow(max(dot(v, r), 0.0), 3.0);\n"
"    vec3 specular = ks * spec * lightColor;\n"
"\n"
"    lightC = (ambient + diffuse + specular) * color;\n"
"    lightV = (ambient + diffuse + specular) * vColor;}\n"
"    else{\n"
"    lightC = color;\n"
"    lightV = vColor;}\n"
"\n"
"    if(hasColor == true)\n"
"       FragColor = vec4(lightV, 1.0f);\n"
"    else\n"
"       FragColor = vec4(lightC, 1.0f);\n"
"}\0";

/** Create program. 
 *  @author Ricardo Dutra da Silva */
int createShaderProgram()
{
	
    int success;
    char error[512];

    // Request a program and shader slots from GPU
    int program  = glCreateProgram();
    int vertex   = glCreateShader(GL_VERTEX_SHADER);
    int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Set shaders source
    glShaderSource(vertex, 1, &vertex_code, NULL);
    glShaderSource(fragment, 1, &fragment_code, NULL);

    // Compile shaders
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
	glGetShaderInfoLog(vertex, 512, NULL, error);
	std::cout << "ERROR: Shader comilation error: " << error << std::endl;
    }
                
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
	glGetShaderInfoLog(fragment, 512, NULL, error);
	std::cout << "ERROR: Shader comilation error: " << error << std::endl;
    }

    // Attach shader objects to the program
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // Build program
    glLinkProgram(program);
    glGetShaderiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
	glGetProgramInfoLog(program, 512, NULL, error);
	std::cout << "ERROR: Program link error: " << error << std::endl;
    }

    // Get rid of shaders (not needed anymore)
    glDetachShader(program, vertex);
    glDetachShader(program, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}
