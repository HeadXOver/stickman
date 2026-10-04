#include "pch.h"
#include "scene.h"

yuanEngine::Scene::Scene()
{
}

yuanEngine::Scene& yuanEngine::Scene::get_instance()
{
    static Scene instance;
    return instance;
}
