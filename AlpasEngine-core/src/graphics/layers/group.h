#pragma once

#include "../renderable2d.h"

namespace alpas { namespace graphics {

	class Group : public Renderable2D
	{
	private:
		std::vector<Renderable2D*> m_Renderables;
		maths::mat4 m_TransformationMatrix;
	public:
		Group();

	};
	}
}