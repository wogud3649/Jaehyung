#pragma once
class TutorialScene : public Scene
{
public:
	TutorialScene();
	virtual ~TutorialScene();

	virtual void Update() override;
	virtual void Render() override;
private:
	shared_ptr<VertexBuffer>	 _vertexBuffer;

	shared_ptr<VertexShader>	 _vs;
	shared_ptr<PixelShader>		 _ps;
	shared_ptr<SRV>				 _srv;
	shared_ptr<SamplerState>	 _sampler;
};

