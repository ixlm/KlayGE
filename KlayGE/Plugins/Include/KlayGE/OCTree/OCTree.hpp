// OCTree.hpp
// KlayGE 八叉树类 头文件
// Ver 2.4.0
// 版权所有(C) 龚敏敏, 2004-2005
// Homepage: http://klayge.sourceforge.net
//
// 2.4.0
// 改用线性八叉树 (2005.3.20)
//
// 2.1.2
// 初次建立 (2004.6.15)
//
// 修改记录
//////////////////////////////////////////////////////////////////////////////////

#ifndef _OCTREE_HPP
#define _OCTREE_HPP

#include <KlayGE/PreDeclare.hpp>
#include <KlayGE/SceneNode.hpp>
#include <KlayGE/SceneManager.hpp>
#include <KlayGE/Box.hpp>

#include <vector>
#include <map>
#include <string>

#include <KlayGE/OCTree/OCTreeFrustum.hpp>

#ifdef KLAYGE_DEBUG
	#pragma comment(lib, "KlayGE_Scene_OCTree_d.lib")
#else
	#pragma comment(lib, "KlayGE_Scene_OCTree.lib")
#endif

namespace KlayGE
{
	class OCTree : public SceneManager
	{
	public:
		typedef std::string tree_id_t;

	public:
		OCTree(Box const & box);

		void ClipScene(Camera const & camera);
		void PushRenderable(RenderablePtr const & obj);

	private:
		tree_id_t Child(tree_id_t const & id, int child_no);
		Box AreaBox(tree_id_t const & id);
		bool InsideChild(tree_id_t const & id, RenderablePtr const & renderable);
		void InsertRenderable(tree_id_t const & id, RenderablePtr const & renderable);

	private:
		OCTree(OCTree const & rhs);
		OCTree& operator=(OCTree const & rhs);

	private:
		typedef std::map<tree_id_t, RenderablePtr> linear_octree_t;
		linear_octree_t linear_octree_;
		Box root_box_;

		std::vector<RenderablePtr> uncullables_;

		OCTreeFrustum frustum_;
	};
}

#endif		// _OCTREE_HPP
