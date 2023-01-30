#include "../Editor/Editor.h"
#include "../Common/Engine.h"
#include "../Entity/Component.h"
#include "../Entity/GameObject.h"
#include "../World/Scene.h"
#include "../Render/Renderer.h"
#include "../Render/Window.h"

constexpr ImVec4 IM_COLOR_GRAY		= { 0.7f, 0.7f, 0.7f, 1.0f };
constexpr ImVec4 IM_COLOR_ORANGE	= { 1.0f, 0.8f, 0.0f, 1.0f };

Hudson::Editor::Editor::Editor(Common::Engine* engine, ComponentRegistry* registry) : _engine(engine), _registry(registry)
{
	engine->RegisterPreFrameHook([](Common::Engine* engine)
		{
			engine->GetRenderer()->SetImguiDockspace(true);
		});

	engine->RegisterMidFrameHook([this](Common::Engine* engine)
		{
			this->Draw();
		});
}

Hudson::Editor::Editor::~Editor()
{

}

void Hudson::Editor::Editor::InfiniteButton()
{
	if (ImGui::BeginMenu("Make Engine"))
	{
		ImGui::MenuItem("Load Components...");
		ImGui::MenuItem("Load Engine Stuff...");

		if (ImGui::BeginMenu("Make Game"))
		{
			ImGui::MenuItem("The Motor Speedway of the South");
			ImGui::MenuItem("Some Sort of Roguelike");
			ImGui::MenuItem("Black Ops 2 - Remastered");
			ImGui::MenuItem("Half-Life 3");

			if (ImGui::BeginMenu("Finish Game..."))
			{
				InfiniteButton();
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
}

void Hudson::Editor::Editor::MenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Very Useful Menu"))
		{
			if (ImGui::MenuItem("File"))
			{

			}
			if (ImGui::MenuItem("Inputs"))
			{

			}

			if (ImGui::BeginMenu("Build"))
			{
				ImGui::MenuItem("Doc Hudson");
				ImGui::MenuItem("Lightning McQueen");
				ImGui::MenuItem("Chick Hicks");

				if (ImGui::BeginMenu("More..."))
				{
					ImGui::MenuItem("Tow Mater");
					ImGui::MenuItem("Strip Weathers");

					if (ImGui::BeginMenu("Even More..."))
					{
						InfiniteButton();
						ImGui::EndMenu();
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		ImGui::Separator();

		if (ImGui::BeginMenu("Scenes"))
		{
			if (ImGui::MenuItem("New Empty Scene"))
			{
				_engine->GetSceneManager()->AddScene(new World::Scene());
			}
			ImGui::MenuItem("Load Scene...", 0, false, false);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Debug"))
		{
			ImGui::MenuItem("Show IDs", "", &_showIds);
			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Help", 0, &_showHelp));

		ImGui::EndMainMenuBar();
	}
}

void Hudson::Editor::Editor::Scene()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoScrollbar);
	//ImGui::Scale
	ImTextureID textureID = reinterpret_cast<ImTextureID>(_engine->GetRenderer()->GetRenderedSceneTexture());

	// TODO take an Unreal approach and make it so that the image caps at a certain size
	ImVec2 imageSize = { ImGui::GetContentRegionAvail().x,ImGui::GetContentRegionAvail().y };

	ImVec2 uv_min = ImVec2(0.0f, 1.0f); // Top-left
	ImVec2 uv_max = ImVec2(1.0f, 0.0f); // Lower-right
	ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
	ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white

	ImGui::Image(textureID, imageSize, uv_min, uv_max, tint_col, border_col);

	// TODO clean this up, doesnt need to run every frame but testing for now
	// TODO detect a change easy enough
	if(imageSize.x > 0 && imageSize.y > 0)
	{
		// Framebuffer can't have 0 or less so, this queues framebuffer recreate for when the application isnt minimized
		_engine->GetRenderer()->CreateFramebuffers(imageSize.x, imageSize.y);
	}

	ImGui::End();
	ImGui::PopStyleVar();
}

void Hudson::Editor::Editor::Hierarchy()
{
	ImGui::Begin("Hierarchy");

	auto scenes = _engine->GetSceneManager()->GetLoadedScenes();
	int i = 0, j = 0;
    for (auto scene : scenes)
    {
		ImGui::SetNextItemOpen(true, ImGuiCond_Once);

		if (ImGui::TreeNode((void*)(intptr_t)i, "Scene %d - %s", i, scene->GetName().c_str()))
		{

			if (ImGui::BeginPopupContextItem())
			{
				ImGui::PushID(&scene);
				ImGui::InputText("", &scene->_name);
				ImGui::PopID();
				ImGui::Separator();
				if (ImGui::MenuItem("Active?", 0, scene->IsActive()))
				{
					scene->SetActive(!scene->IsActive());
				}
				if (ImGui::MenuItem("Rendering?", 0, scene->IsRendering()))
				{
					scene->SetRendering(!scene->IsRendering());
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Create Empty Object"))
				{
					scene->AddObject(new Entity::GameObject());
				}
				if (ImGui::MenuItem("Paste Object", 0, false, false))
				{
					// TODO: object/component clipboard
				}
				ImGui::Separator();
				if (ImGui::MenuItem("Save Scene...", 0, false, false))
				{
					// TODO: save
				}
				if (ImGui::MenuItem("Duplicate Scene", 0, false, false))
				{
					// TODO: duplicate
				}
				if (ImGui::MenuItem("Delete Scene (!)"))
				{
					_selectedObj = nullptr;
					_engine->GetSceneManager()->RemoveScene(scene);
				}
				ImGui::EndPopup();
			}
		    for (auto object : scene->GetObjects())
            {
				ImGuiTreeNodeFlags objNodeFlags = ImGuiTreeNodeFlags_Leaf;
				if (_selectedObj == object)
				{
					objNodeFlags |= ImGuiTreeNodeFlags_Selected;
				}
				ImGui::TreeNodeEx((void*)(intptr_t)j, objNodeFlags, "(%d) %s", j, object->GetName().c_str());
				ImGui::TreePop();
				if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
				{
					_selectedObj = object;
				}
				if (ImGui::BeginPopupContextItem())
				{
					if (ImGui::MenuItem("Save Object...", 0, false, false))
					{
						// TODO: save
					}
					if (ImGui::MenuItem("Copy Object", 0, false, false))
					{
						// TODO: copy
					}
					if (ImGui::MenuItem("Delete Object"))
					{
						ImGui::CloseCurrentPopup();
						if (_selectedObj == object)
						{
							_selectedObj = nullptr;
						}
						scene->RemoveObject(object);
					}
					ImGui::EndPopup();
				}
				++j;
            }
			ImGui::TreePop();
		}

		j = 0;
		++i;
    }

	ImGui::End();
}

void Hudson::Editor::Editor::ContentBrowser()
{
	ImGui::Begin("Content Browser");

	ImGui::TextColored(IM_COLOR_GRAY, "Not yet implemented");

	ImGui::End();
}

void Hudson::Editor::Editor::ComponentList()
{
	ImGui::Begin("Components List");

	if (_registry)
	{
		if (_registry->GetKnownComponents().empty())
		{
			ImGui::TextColored(IM_COLOR_ORANGE, "No components registered!");
		}
		else if (_selectedObj == nullptr)
		{
			ImGui::TextColored(IM_COLOR_GRAY, "Select an object from Hierarchy.");
		}
		else
		{
			ImGui::TextColored(IM_COLOR_GRAY, "Select a component below to add.");

			for (auto& element : _registry->GetKnownComponents())
			{
				ImGui::Text(element.name.c_str());
				ImGui::SameLine();
				ImGui::PushID((void*)(&element));
				if (ImGui::SmallButton("+"))
				{
					// Add the component
					auto component = element.constructor();
					_selectedObj->AddComponent(component);
				}
				ImGui::PopID();
			}

		}
	}
	else
	{
		ImGui::TextColored(IM_COLOR_ORANGE, "No ComponentRegistry found!");
	}

	ImGui::End();
}

void Hudson::Editor::Editor::ObjectProperties()
{
	ImGui::Begin("Object Properties");

	if (_selectedObj == nullptr)
	{
		ImGui::TextColored(IM_COLOR_GRAY, "Select an object from Hierarchy.");
	}
	else
	{
		if (ImGui::BeginTable("ObjEditor", 2, ImGuiTableFlags_Resizable))
		{
			ImGui::TableNextColumn();

		    ImGui::Text("Name");
			ImGui::TableNextColumn();

			ImGui::PushID("ObjEditor_Rename");
			ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
			ImGui::InputText("", &_selectedObj->GetName());
			ImGui::PopID();
		    ImGui::TableNextColumn();

			if (_showIds)
			{
				ImGui::Text("Runtime ID (?)");
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("The runtime ID (pointer) is logged in debug messages.");
				ImGui::TableNextColumn();

				ImGui::Text("%p", (void*)_selectedObj);
				ImGui::TableNextColumn();

				ImGui::Text("Serial ID (?)");
				if (ImGui::IsItemHovered()) ImGui::SetTooltip("The serial ID is stored in .scene files. (WIP)");
				ImGui::TableNextColumn();

				ImGui::Text("%u", /*_selectedObj.GetSerialID()*/ 0); // TODO
				ImGui::TableNextColumn();
			}

			ImGui::Text("Position");
			ImGui::TableNextColumn();

			ImGui::PushID("ObjEditor_Pos");
			ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
			ImGui::DragFloat2("", &_selectedObj->GetTransform().pos.x, 0.5f);
			ImGui::PopID();
			ImGui::TableNextColumn();

			ImGui::Text("Scale");
			ImGui::TableNextColumn();

			ImGui::PushID("ObjEditor_Scale");
			ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
			ImGui::DragFloat2("", &_selectedObj->GetTransform().scale.x, 0.5f);
			ImGui::PopID();
			ImGui::TableNextColumn();

			ImGui::Text("Rotation");
			ImGui::TableNextColumn();

			ImGui::PushID("ObjEditor_Rotate");
			ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
			ImGui::DragFloat("", &_selectedObj->GetTransform().rotateZ, 0.5f);
			ImGui::PopID();
			ImGui::TableNextColumn();

			ImGui::EndTable();
		}

        for (auto component : _selectedObj->GetAllComponents())
        {
			Common::IEditable* editable = dynamic_cast<Common::IEditable*>(component);
			ImGuiTreeNodeFlags headerFlags = 0;
			if (!editable && !_showIds)
				headerFlags |= ImGuiTreeNodeFlags_Leaf;

			ImGui::PushID((void*)component);
			bool compOpen = ImGui::CollapsingHeader(component->GetTypeName(), headerFlags);
			if (ImGui::BeginPopupContextItem())
			{
				if (ImGui::MenuItem("Copy Component...", 0, false, false))
				{
					// TODO
				}
				if (ImGui::MenuItem("Delete Component"))
				{
					component->GetParent()->RemoveComponent(component);
				}
				ImGui::EndPopup();
			}
			if (compOpen)
			{
				if (_showIds)
				{
					if (ImGui::BeginTable("CompEditor", 2, ImGuiTableFlags_Resizable))
				    {
						ImGui::TableNextColumn();
						ImGui::Text("Runtime ID (?)");
						if (ImGui::IsItemHovered()) ImGui::SetTooltip("The runtime ID (pointer) is logged in debug messages.");
						ImGui::TableNextColumn();

						ImGui::Text("%p", (void*)_selectedObj);
						ImGui::TableNextColumn();

						ImGui::Text("Serial ID (?)");
						if (ImGui::IsItemHovered()) ImGui::SetTooltip("The serial ID is stored in .scene files. (WIP)");
						ImGui::TableNextColumn();

						ImGui::Text("%u", _selectedObj->GetSerialID()); // TODO
						ImGui::EndTable();
					}
				}

				if (editable)
				{
					editable->DrawPropertyUI();
				}
			}
			ImGui::PopID();
        }
	}

	ImGui::End();
}

void Hudson::Editor::Editor::Tools()
{
	ImGui::Begin("Tools");
	ImGui::TextColored(IM_COLOR_GRAY, "Not yet implemented");
	ImGui::End();
}

void Hudson::Editor::Editor::Debug()
{
	ImGui::Begin("Debug");
	ImGui::TextColored(IM_COLOR_GRAY, "Not yet implemented");
	ImGui::End();
}

void Hudson::Editor::Editor::Help()
{
	if (ImGui::BeginPopupModal("'How to Hudson', a memoir by best-selling author Doc Hudson", &_showHelp))
	{
		ImGui::Text("Just try right-clicking things to see what menus exist");
		ImGui::Text("The end");

		ImGui::EndPopup();
	}

	if (_showHelp)
		ImGui::OpenPopup("'How to Hudson', a memoir by best-selling author Doc Hudson");
}

void Hudson::Editor::Editor::Draw()
{
	MenuBar();
	Scene();
	Hierarchy();
	ContentBrowser();
	ComponentList();
	ObjectProperties();
	Tools();
	Debug();
	Help();
}

