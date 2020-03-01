#include "RenderPass.h"
#include "AbstractMapper.h"
#include "DeferredRenderer.h"
#include "Framebuffer.h"

void RenderPass::setNumberOfOutputPorts(UINT numberOfPorts)
{
	outputs = std::vector<std::shared_ptr<FramebufferAttachment>>(numberOfPorts);
	for (UINT i = 0; i < outputs.size(); i++)
	{
		outputs[i] = std::make_shared<FramebufferAttachment>();
	}
}

void RenderPass::render(DeferredRenderer* ren)
{
	framebuffer->bind();

	clearFramebuffer(ren);

	bind(ren);

	if (passType == RenderPassType::FULL_PASS)
		ren->fullPass();
	else if (passType == RenderPassType::QUAD_PASS)
		ren->quadPass();
	else
	{
		for (UINT i = 0; i < mappers.size(); i++)
		{
			if (mappers[i]->use(ren))
				mappers[i]->draw(ren);
		}
	}

	framebuffer->unbind();
}

void RenderPass::clearFramebuffer(DeferredRenderer* ren) { framebuffer->clear(); }