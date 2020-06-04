#pragma once

#include "src/gamestate/state.h"
#include "src/components/Icomponents.h"
#include "src/foundation/objobject.h"
#include "src/utilities/light.h"
// during car racing
class RacingState: public State
{
public:
    RacingState() = delete;
    RacingState(std::shared_ptr<GameData> data_ptr);
    ~RacingState();
    void init() override;
    void update() override;
    void render() override;
    void handle_input(GLFWwindow *window) override; // handle input from inputmanager
    void pause() override;
    void resume() override;
    int width;
    int height;
    GLMatrices m_mat;
    
private:
    FreeCam cam;
    objobject cyborg;
    objobject cyborg2;
    DirectionalLight dirlight;
    //Coin coin;
    std::shared_ptr<Shader> model_shader_ptr;
    std::shared_ptr<Shader> monotone_shader_ptr;
    std::shared_ptr<Shader> lighting_shader_ptr;
    GLuint test_VAO;
    GLuint test_VBO;
    
    /* OBJECTS TO BE DRAWN
     
     Tree
     PlayerCar
     Castle
     Coin
     ...other obstacles
     
     */
};
