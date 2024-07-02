#include "NWengineCore.h"	
#include "nwin/window.h"
#include "player.h"



void Init() {
    //Configuration for imgui
    NWin::Window* win = (NWin::Window*)Context::window;
    //---------------------------------------------------
    Scene& s = Scene::CreateNew("Scene0");
    s.MakeCurrent();
    GameObject& obj = s.AddObject(); 
    obj.AddComponent<Transform>();
    Sprite& spr = *obj.AddComponent<Sprite>();
    spr.SetShader(ShaderTexturedDefaultStr, &ShaderTexturedDefaultID); spr.SetTexture(&ImageDefault, &TextureDefaultID);
    obj.AddComponent<Camera>()->Use();
    obj.GetComponent<Camera>()->ChangeOrtho(Context::WINDOW_WIDTH, Context::WINDOW_HEIGHT);
    obj.AddComponent<Collider>()->Start();
    Script* plyr = obj.AddComponent<Script>(); 
    plyr->SetScript<player>();

     
    GameObject& wall = s.AddObject(); 
    auto t = wall.AddComponent<Transform>();
    t->position.y -= 100.0;
    t->scale.x = 20.0;
    Sprite& spr0 = *wall.AddComponent<Sprite>();
    spr0.SetShader(ShaderTexturedDefaultStr, &ShaderTexturedDefaultID); spr0.SetTexture(&ImageDefault, &TextureDefaultID);
    wall.AddComponent<Collider>()->Start();
    
    GameObject& wall0 = s.AddObject(); 
    auto t0 = wall0.AddComponent<Transform>();
    t0->position.x -= 100.0;
    t0->scale.y = 15.0;
    Sprite& spr1 = *wall0.AddComponent<Sprite>();
    spr1.SetShader(ShaderTexturedDefaultStr, &ShaderTexturedDefaultID); 
    spr1.SetTexture(&ImageDefault, &TextureDefaultID);
    wall0.AddComponent<Collider>()->Start();
}

void Render() {
    (*Renderer::currentRenderer)(true); 
}


int main() {

	NWenginePushFunction(ON_MAIN_CALL_LOCATION::InitEnd, Init);
    NWenginePushFunction(ON_MAIN_CALL_LOCATION::FrameIntermediate, Render);
	NWengineInit();
	NWengineLoop();
	NWengineShutdown();
    
	return 0;
}

