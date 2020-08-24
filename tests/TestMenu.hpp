
#include "../source/core/Layer.hpp"

namespace test
{

class TestMenu : public Layer
{
public:
    const char* LayerName() const override { return "TestMenu"; }
    void OnUpdate(float deltaTime) override;
    void OnGuiRender() override;
    ~TestMenu();

private:
    Layer* test = nullptr;
};

}