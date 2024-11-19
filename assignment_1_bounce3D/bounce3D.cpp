#include "Model.h"

ECSCoordinator gCoordinator;

void _register_components(){
	gCoordinator.RegisterComponent<ElementBuffer>();
}

void _register_systems(){

}


int main(){
	gCoordinator.Init();
	return 0;
}