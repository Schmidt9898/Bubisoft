#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <iostream>
#include <vector>

/*
extern glfwWindow* window;

Struct Model{
    glm::mat4 skeleton[32][160];
    VAO vao;

    void draw(){
        glfwMakeContextCurrent(window);

        /*bind vao*/
        /*interpolate matrices*/
        /*upload matrices*/
        /*draw vao*/
//    }
//};
/*
run, jump, swim, levitate, fall, ride,
attack_1h x2, attack_2h, block, cast x2 (can be the same as shoot? 1h1h),
cast_2h, shoot x4, reload x3, sheathe x??,
idle, crouch, stunned, combat_stance?(1H1H, 2H, Ranged1H_pistol, Ranged2H,)
use, sit x2, touch, map
about 32 animations with average 5 cap/sec = 160 poses
==avg 5 mat per bone
*/
struct node{
    node* parent;
    std::vector< node* > child;
    std::string name;
    unsigned id;
    glm::mat4 trans;

    node( node* _p, std::string _n) : parent(_p), name(_n){
        if(parent == nullptr)
            std::cout<<"\nNew node "<<name<<", root/no parent";
        else
            std::cout<<"\nNew node "<<name<<", parent "<<parent->name;


    }

    void list_nodes(std::string tab){
        std::cout<<tab<<name<<"("<<child.size()<<")";
        if(child.size()==0) return;
        for(unsigned i = 0; i<child.size(); i++)
            child[i]->list_nodes((std::string)(tab+"-"));
    }

    ~node(){
        for(unsigned i = 0; i<child.size(); i++){
            std::cout<<"\nDeleting child"<<child[i]->name;
            delete child[i];
        }
    }

    void assignId(std::string &_name, unsigned &_id){
        if(name==_name) id=_id;
        else {
            for(unsigned i = 0; i < child.size(); i++){
                child[i]->assignId(_name, _id);
            }
        }
    }
};

struct Armature{
    node* root;
    node* current;
    Armature(){
        root=new node(nullptr, "Root");
        current=root;
        root->parent=root;
    }

    ~Armature(){
        delete root;
    }

    void listEm(){
        root->list_nodes("\n");
    }

    void addNodeId(std::string &_name, unsigned &id){
        root->assignId(_name, id);
    }
};


/*
struct Joint
/* usage:
*   j[0]->calcBind(glm::mat4(1.0));once
*   j[0]->calcJoint(quat); every frame

{
public:
    static unsigned num_joints;
    unsigned id;
    glm::vec3 pos;
    glm::quat rot;

    Joint* child;
    glm::mat4 invAbsoluteTransform;//this is basically a constant, but i cant set it on creation
    glm::mat4 jointTransform;//changes every frame, could be reference

    Joint(glm::vec3 _pos)
    {
        rot = glm::angleAxis(glm::radians(0.f), glm::vec3(0.0f, 0.0f, 0.0f));
        id = num_joints;
        num_joints++;
        pos = _pos;
        child = nullptr;
    }

    glm::mat4 getLocalBind()
    {
        return (glm::translate(glm::mat4(1.0f),pos));
    }

    void calcBind(glm::mat4 absoluteParent)
    {
        invAbsoluteTransform = getLocalBind() * absoluteParent;
        if(child)
        {
            child->calcBind(invAbsoluteTransform);
        }
        invAbsoluteTransform = glm::inverse(invAbsoluteTransform);
    }

    void calcJoint(glm::quat _rot, glm::mat4 parentTransform)
    {
        jointTransform = parentTransform * (glm::toMat4(_rot)) * (glm::translate(glm::mat4(1.0f),pos));
        if(child)
        {
            child->calcJoint(_rot, jointTransform);
        }
        jointTransform*=invAbsoluteTransform;
    }

};
unsigned Joint::num_joints = 0;
*/
















#endif // MODEL_H_INCLUDED
