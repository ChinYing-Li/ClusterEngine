float vertices[] = {
     0.5f,  0.5f, -0.2f,  // top right
     0.5f, -0.5f, -0.2f,  // bottom right
    -0.5f, -0.5f, -0.2f,  // bottom left
    -0.5f,  0.5f, -0.2f   // top left
};

unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};
std::vector<unsigned int> ind = {0,1,2,1,2,3};
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);
glGenBuffers(1, &EBO);

glBindVertexArray(VAO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, 18*sizeof(float), vertices, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), &ind[0], GL_STATIC_DRAW);
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

glBindVertexArray(0);
//glBindBuffer(GL_ARRAY_BUFFER, 0);
//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
