//#include "F:/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
//#include "F:/home/codeleaded/System/Static/Library/Random.h"
//#include "F:/home/codeleaded/System/Static/Library/RayCast.h"
//#include "F:/home/codeleaded/System/Static/Library/Thread.h"
//#include "F:/home/codeleaded/System/Static/Library/ImageFilter.h"

#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/RayCast.h"
#include "/home/codeleaded/System/Static/Library/Thread.h"
#include "/home/codeleaded/System/Static/Library/ImageFilter.h"
#include "/home/codeleaded/System/Static/Library/VoxelWorld.h"
#include "/home/codeleaded/System/Static/Library/Selector.h"

void Fn_Render(
    Block* b,
    unsigned int* Target,
    int Width,
    int Height,
    float x,float y,
    float w,float h
){
	const Pixel p = Block_Pixel(*b,SIDE_TOP);
	Rect_RenderXX(Target,Width,Height,x,y,w,h,p);
}

Block selected;
Selector selector;
VoxelWorld voxelworld;

void Menu_Set(int m){
	if(voxelworld.menu==0 && m==1){
		AlxWindow_Mouse_SetInvisible(&window);
		SetMouse((Vec2){ GetWidth() / 2,GetHeight() / 2 });
	}
	if(voxelworld.menu==1 && m==0){
		AlxWindow_Mouse_SetVisible(&window);
	}
	
	voxelworld.mousebefore = GetMouse();
	voxelworld.menu = m;
}

void Setup(AlxWindow* w){
	Menu_Set(0);

	selector = Selector_New(
        (Block[]){
            BLOCK_VOID,
			BLOCK_BEDROCK,
			BLOCK_DIRT,
			BLOCK_STONE,
			BLOCK_GRASS,
			BLOCK_GRAS,
			BLOCK_LEAF,
			BLOCK_LOGS,
			BLOCK_LOG,
			BLOCK_TORCH,
			BLOCK_COLE,
			BLOCK_COPPER,
			BLOCK_IRON,
			BLOCK_GOLD,
			BLOCK_DIAMONDS,
			BLOCK_RUBIES,
			BLOCK_SAPPHIRES,
			BLOCK_EMERALDS,
			BLOCK_GRANITE,
			BLOCK_BASALT,
			BLOCK_SANDSTONE,
			BLOCK_LIMESTONE,
			BLOCK_CLAYSTONE,
			BLOCK_GNEISS,
			BLOCK_SLATE
        },
        sizeof(Block),
        25U,
        LIGHT_GRAY,
        0.05f,0.05f,0.9f,0.9f,
        0.10f,0.2f,
        (void(*)(void*,unsigned int*,int,int,float,float,float,float))Fn_Render
    );

	voxelworld = VoxelWorld_New(
		Figure3D_New(
			Vec3D_New(0.0f,0.0f,0.0f),
			Vec3D_New(0.5f,1.4f,0.5f),
			Vec3D_New(0.0f,-10.0f,0.0f),
			1,
			(unsigned int[]){
				0xFFAAAA00,//1,
				0xFF000088,//1,
				0xFFAAAA00,//1,
				0xFFAAAA00,//1,
				0xFF111111,//1,
				0xFF111111,//1,
				0xFF333333,//1,
				0xFF333333//1
			}
		),
		"./assets/Own_Atlas.png",
		"./data/Test"
	);
	VoxelWorld_Start(&voxelworld);
}
void Update(AlxWindow* w){
	if(voxelworld.menu==1){
		if(GetMouse().x!=voxelworld.mousebefore.x || GetMouse().y!=voxelworld.mousebefore.y){
			Vec2 d = Vec2_Sub(GetMouse(),voxelworld.mousebefore);
			Vec2 a = Vec2_Mulf(Vec2_Div(d,(Vec2){ window.Width,window.Height }),F32_PI2);
	
			Figure3D* fig = VoxelWorld_GetFigure(&voxelworld);
			fig->a.y += a.x;
			fig->a.x += a.y;
	
			SetMouse((Vec2){ GetWidth() / 2,GetHeight() / 2 });
			voxelworld.mousebefore = GetMouse();
		}
	}
	
	if(Stroke(ALX_KEY_ESC).PRESSED){
		Menu_Set(!voxelworld.menu);
		Selector_State(&selector,!selector.visible);
	}

	if(Stroke(ALX_KEY_Z).PRESSED)
		VoxelWorld_Cubes_Mode(&voxelworld,voxelworld.mode + 1);

	if(Stroke(ALX_KEY_C).PRESSED){
		Figure3D* fig = VoxelWorld_GetFigure(&voxelworld);
		fig->OnView = fig->OnView < 3 ? fig->OnView + 1 : 0;
	}
	if(Stroke(ALX_KEY_B).PRESSED){
		Figure3D* fig = VoxelWorld_GetFigure(&voxelworld);
		fig->OnCollision = fig->OnCollision < 1 ? fig->OnCollision + 1 : 0;
	}

	if(Stroke(ALX_KEY_R).DOWN) 		Figure3D_AccUp(VoxelWorld_GetFigure(&voxelworld),5.0f);
	else if(Stroke(ALX_KEY_F).DOWN) Figure3D_AccUp(VoxelWorld_GetFigure(&voxelworld),-5.0f);
	else							Figure3D_AccUp(VoxelWorld_GetFigure(&voxelworld),0.0f);
	
	if(Stroke(ALX_KEY_W).DOWN) 	Figure3D_AccForward(VoxelWorld_GetFigure(&voxelworld),20.0f * w->ElapsedTime);
	if(Stroke(ALX_KEY_S).DOWN) 	Figure3D_AccForward(VoxelWorld_GetFigure(&voxelworld),-20.0f * w->ElapsedTime);
	if(Stroke(ALX_KEY_A).DOWN) 	Figure3D_AccLeft(VoxelWorld_GetFigure(&voxelworld),20.0f * w->ElapsedTime);
	if(Stroke(ALX_KEY_D).DOWN)  Figure3D_AccLeft(VoxelWorld_GetFigure(&voxelworld),-20.0f * w->ElapsedTime);

	if(selector.visible){
		if(Stroke(ALX_MOUSE_L).PRESSED){
    	    Block* b = (Block*)Selector_Interact(
    	        &selector,
    	        GetMouse().x / (float)GetWidth(),
    	        GetMouse().y / (float)GetHeight()
    	    );
			if(b) selected = *b;
    	}
	
    	if(Stroke(ALX_MOUSE_S_UP).PRESSED){
    	    Selector_Offset(&selector,-1);
    	}
    	if(Stroke(ALX_MOUSE_S_DOWN).PRESSED){
    	    Selector_Offset(&selector,1);
    	}
	}else{
		if(Stroke(ALX_MOUSE_L).PRESSED) VoxelWorld_Place(&voxelworld,BLOCK_VOID,4.0f);
		if(Stroke(ALX_MOUSE_R).PRESSED) VoxelWorld_PlaceN(&voxelworld,selected,4.0f);
	}

	VoxelWorld_Update(&voxelworld,w->ElapsedTime);

	Clear(LIGHT_BLUE);
	VoxelWorld_Render(WINDOW_STD_ARGS,&voxelworld);

	Selector_Render(&selector,WINDOW_STD_ARGS,GetMouse().x / (float)GetWidth(),GetMouse().y / (float)GetHeight());

	String str = String_Format("X: %f, Y: %f, Z: %f, Size: %d",VoxelWorld_GetFigure(&voxelworld)->p.x,VoxelWorld_GetFigure(&voxelworld)->p.y,VoxelWorld_GetFigure(&voxelworld)->p.z,(Number)Voxel_World_Tris(&voxelworld.map));
	RenderCStrSize(str.Memory,str.size,0,0,RED);
	String_Free(&str);
}
void Delete(AlxWindow* w){
	VoxelWorld_Free(&voxelworld);
	AlxWindow_Mouse_SetVisible(&window);
}

int main(){
    if(Create("Voxel3D",2500,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}