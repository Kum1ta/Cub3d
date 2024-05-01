/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.inl                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psalame <psalame@student.42angouleme.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:13:55 by maldavid          #+#    #+#             */
/*   Updated: 2024/04/16 10:47:27 by psalame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <core/graphics.h>
#include <iostream>

namespace mlx
{
	int& GraphicsSupport::getID() noexcept { return _id; }
	std::shared_ptr<MLX_Window> GraphicsSupport::getWindow() { return _window; }

	void GraphicsSupport::clearRenderData() noexcept
	{
		MLX_PROFILE_FUNCTION();
		_drawStrList.clear();
		_drawImgList.clear();
		_pixel_put_pipeline.clear();
		_text_manager.clear();
		_texture_manager.clear();
	}

	void GraphicsSupport::pixelPut(int x, int y, std::uint32_t color) noexcept
	{
		MLX_PROFILE_FUNCTION();
		_pixel_put_pipeline.setPixel(x, y, color);
	}

	void GraphicsSupport::stringPut(int x, int y, std::uint32_t color, std::string str)
	{
		MLX_PROFILE_FUNCTION();
		std::pair<DrawableResource*, bool> res = _text_manager.registerText(x, y, color, str);
		if(!res.second) // if this is not a completly new text draw
		{
			auto it = std::find(_drawStrList.begin(), _drawStrList.end(), res.first);
			if(it != _drawStrList.end())
				_drawStrList.erase(it);
		}
		_drawStrList.push_back(res.first);
	}

	void GraphicsSupport::texturePut(Texture* texture, int x, int y)
	{
		MLX_PROFILE_FUNCTION();
		auto res = _texture_manager.registerTexture(texture, x, y);
		if(!res.second) // if this is not a completly new texture draw
		{
			auto it = std::find(_drawImgList.begin(), _drawImgList.end(), res.first);
			if(it != _drawImgList.end())
				_drawImgList.erase(it);
		}
		_drawImgList.push_back(res.first);
	}

	void GraphicsSupport::loadFont(const std::filesystem::path& filepath, float scale)
	{
		MLX_PROFILE_FUNCTION();
		_text_manager.loadFont(*_renderer, filepath, scale);
	}
}
