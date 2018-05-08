/*
The78ester
*/

#include <ofxImGui.h>
#include "ofxImGuiParameter.h"

#if 0
#include <ofxXmlSettings.h>

#else
typedef class ofxXmlSettings2ofXml
{
public:
	bool load(std::string const& p)
	{
		bool yes = m_xml.load(p);
		if (yes)
		{
			m_xml.setToParent();
		}
		return yes;
	}

	bool save(std::string const& p)
	{
		return m_xml.save(p);
	}

	bool tagExists(std::string const& tag)
	{
		return m_xml.exists(tag);
	}

	int addTag(std::string const& tag)
	{
		bool yes = m_xml.addChild(tag);
		if (!yes)
		{
			return -1;
		}
		return m_xml.getNumChildren(tag) - 1;
	}

	bool pushTag(const std::string& tag, int which = 0)
	{
		return m_xml.setTo(tag);
	}

	int	popTag()
	{
		m_xml.setToParent();
		return 0;
	}

	template < typename T >
	T getValue(const std::string& tag, T const& defaultValue)
	{
		if (!m_xml.exists(tag))
		{
			return defaultValue;
		}

		return m_xml.getValue< T >(tag, T());
	}

	std::string getValue(const std::string& tag, char const* defaultValue)
	{
		return getValue<std::string>(tag, defaultValue);
	}

	template< typename T>
	T getAttribute(const std::string& tag, const std::string& attribute, T const& defaultValue, int n = 0)
	{
		bool yes = m_xml.setTo(tag);
		if (!yes)
		{
			m_xml.setToParent();
			return defaultValue;
		}

		std::string val = m_xml.getAttribute(attribute);
		m_xml.setToParent();
		if (val == "")
		{
			return defaultValue;
		}

		return ofFromString<T>(val);
	}

	std::string getAttribute(const std::string& tag, const std::string& attribute, char const* defaultValue, int n = 0)
	{
		return getAttribute<std::string>(tag, attribute, defaultValue, n);
	}

	template< typename T >
	int	setAttribute(const std::string& tag, const std::string& attribute, T const& value, int which = 0)
	{
		bool yes = m_xml.setTo(tag);
		if (!yes)
		{
			m_xml.setToParent();
			return -1;
		}

		yes = m_xml.setAttribute(attribute, ofToString(value));
		m_xml.setToParent();
		if (!yes)
		{
			return -1;
		}

		return 0;
	}

	int setAttribute(const std::string& tag, const std::string& attribute, char const* value, int which = 0)
	{
		return setAttribute< std::string >(tag, attribute, value, which);
	}

	template < typename T >
	int setValue(const std::string&  tag, T const& value, int which = 0)
	{
		if (!m_xml.exists(tag))
		{
			bool yes = m_xml.addChild(tag);
			if (!yes)
			{
				return -1;
			}
		}

		return m_xml.setValue(tag, ofToString(value));
	}

	int setValue(const std::string&  tag, char const* value, int which = 0)
	{
		return setValue<std::string>(tag, value, which);
	}

private:
	ofXml m_xml;
} ofxXmlSettings;

#endif

namespace
{
	typedef std::shared_ptr< ofParameter< ofTexture > > sp_param_tex;
	struct MyTex  
	{
		sp_param_tex	sp_param_texture;
		bool			is_fit_windows;
		bool			is_open;
		bool			is_show_detail;
		uint32_t		id;
	};

	typedef std::shared_ptr< ofParameter< MyTex > > sp_parm_my_tex;

	void gf_draw_bool(ofParameter< bool >* p_param)
	{
		bool b_value = p_param->get();
		bool yes = ImGui::Checkbox(p_param->getName().c_str(), &b_value);
		if (yes)
		{
			p_param->set(b_value);
		}
	}

	void gf_draw_float_slider_default(ofParameter< float >* p_param)
	{
		float f_value = p_param->get();
		bool yes = ImGui::SliderFloat(p_param->getName().c_str(), &f_value, p_param->getMin(), p_param->getMax());
		if (yes)
		{
			p_param->set(f_value);
		}
	}

	void gf_draw_int_slider_default(ofParameter< int >* p_param)
	{
		int i_value = p_param->get();
		bool yes = ImGui::SliderInt(p_param->getName().c_str(), &i_value, p_param->getMin(), p_param->getMax());
		if (yes)
		{
			p_param->set(i_value);
		}
	}

	void gf_draw_float_drag_default(ofParameter< float >* p_param)
	{
		float f_value = p_param->get();
		float delta = p_param->getMax() - p_param->getMin();
		bool yes = ImGui::DragFloat(p_param->getName().c_str(), &f_value, delta * 0.005f ,p_param->getMin(), p_param->getMax());
		if (yes)
		{
			p_param->set(f_value);
		}
	}

	void gf_draw_int_drag_default(ofParameter< int >* p_param)
	{
		int i_value = p_param->get();
		float delta = p_param->getMax() - p_param->getMin();
		bool yes = ImGui::DragInt(p_param->getName().c_str(), &i_value, delta * 0.005f, p_param->getMin(), p_param->getMax());
		if (yes)
		{
			p_param->set(i_value);
		}
	}

	void gf_draw_float_input_default(ofParameter< float >* p_param)
	{
		float f_value = p_param->get();
		float delta = p_param->getMax() - p_param->getMin();
		bool yes = ImGui::InputFloat(p_param->getName().c_str(), &f_value, delta * 0.01f , delta * 0.1f);
		if (yes)
		{
			f_value = ofClamp(f_value, p_param->getMin(), p_param->getMax());
			p_param->set(f_value);
		}
	}

	void gf_draw_int_input_default(ofParameter< int >* p_param)
	{
		int i_value = p_param->get();
		int delta = p_param->getMax() - p_param->getMin();
		int step = delta / 100;
		int step_fast = delta / 10;
		bool yes = ImGui::InputInt(p_param->getName().c_str(), &i_value, step ? step : 1, step_fast ? step_fast : 1);
		if (yes)
		{
			i_value = static_cast<int>(ofClamp(i_value, p_param->getMin(), p_param->getMax()));
			p_param->set(i_value);
		}
	}

	void gf_draw_float_slider_spec(ofParameter< ofxImGuiFloat >* p_param)
	{
		ofxImGuiFloat value_obj = p_param->get();
		bool yes = ImGui::SliderFloat(p_param->getName().c_str(), &value_obj.value, value_obj.arg0, value_obj.arg1);
		if (yes)
		{
			p_param->set(value_obj);
		}
	}

	void gf_draw_float_drag_spec(ofParameter< ofxImGuiFloat >* p_param)
	{
		ofxImGuiFloat value_obj = p_param->get();
		bool yes = ImGui::DragFloat(p_param->getName().c_str(), &value_obj.value, value_obj.arg0, value_obj.arg1);
		if (yes)
		{
			p_param->set(value_obj);
		}
	}

	void gf_draw_float_input_spec(ofParameter< ofxImGuiFloat >* p_param)
	{
		ofxImGuiFloat value_obj = p_param->get();
		bool yes = ImGui::InputFloat(p_param->getName().c_str(), &value_obj.value, value_obj.arg0, value_obj.arg1);
		if (yes)
		{
			p_param->set(value_obj);
		}
	}

	void gf_draw_int_slider_spec(ofParameter< ofxImGuiInt >* p_param)
	{
		ofxImGuiInt value_obj = p_param->get();
		bool yes = ImGui::SliderInt(p_param->getName().c_str(), &value_obj.value, value_obj.arg0, value_obj.arg1);
		if (yes)
		{
			p_param->set(value_obj);
		}
	}

	void gf_draw_int_drag_spec(ofParameter< ofxImGuiInt >* p_param)
	{
		ofxImGuiInt value_obj = p_param->get();
		bool yes = ImGui::DragInt(p_param->getName().c_str(), &value_obj.value, value_obj.arg0, value_obj.arg1);
		if (yes)
		{
			p_param->set(value_obj);
		}
	}

	void gf_draw_int_input_spec(ofParameter< ofxImGuiInt >* p_param)
	{
		ofxImGuiInt value_obj = p_param->get();
		bool yes = ImGui::InputInt(p_param->getName().c_str(), &value_obj.value, value_obj.arg0, value_obj.arg1);
		if (yes)
		{
			p_param->set(value_obj);
		}
	}

	void gf_draw_enum(ofParameter< ofxImGuiEnum >* p_param)
	{
		enum { MaxComboNum = 5, };

		ofxImGuiEnum e_value = p_param->get();
		size_t size_of_enum = e_value.content.size();

		char const** items = new const char*[size_of_enum];
		for (size_t i = 0; i < size_of_enum; ++i)
		{
			items[i] = e_value.content[i].c_str();
		}

		int item2 = (int)e_value.select;
		if (ImGui::Combo(p_param->getName().c_str(), &item2, items, (int)size_of_enum, (int)std::min<size_t>(MaxComboNum, size_of_enum)))
		{
			e_value.select = item2;
			p_param->set(e_value);
		}

		delete[] items;
	}

	void gf_draw_color_u8(ofParameter< ofColor >* p_param)
	{
		ImVec4 color = p_param->get();
		if (ImGui::ColorEdit4(p_param->getName().c_str(), (float*)&color))
		{
			p_param->set(color);
		}
	}

	void gf_draw_color_f32(ofParameter< ofFloatColor >* p_param)
	{
		ImVec4 color = p_param->get();
		if (ImGui::ColorEdit4(p_param->getName().c_str(), (float*)&color))
		{
			p_param->set(color);
		}
	}

	void gf_draw_vec2f(ofParameter< ofVec2f >* p_param)
	{
		ofVec2f vec2f = p_param->get();
		if (ImGui::DragFloat2(p_param->getName().c_str(), vec2f.getPtr()))
		{
			p_param->set(vec2f);
		}
	}

	void gf_draw_vec3f(ofParameter< ofVec3f >* p_param)
	{
		ofVec3f vec3f = p_param->get();
		if (ImGui::DragFloat3(p_param->getName().c_str(), vec3f.getPtr()))
		{
			p_param->set(vec3f);
		}
	}

	void gf_draw_vec4f(ofParameter< ofVec4f >* p_param)
	{
		ofVec4f vec4f = p_param->get();
		if (ImGui::DragFloat4(p_param->getName().c_str(), vec4f.getPtr()))
		{
			p_param->set(vec4f);
		}
	}

	void gf_draw_rect(ofParameter< ofRectangle >*p_param)
	{
		ofRectangle const& rect = p_param->get();
		ofRectangle max_rect = p_param->getMax();
		ofRectangle min_rect = p_param->getMin();
		float len = std::max<float>(max_rect.width - min_rect.width, max_rect.height - min_rect.height);
		if (len <= 0.f)
		{
			len = 1.f;
		}

		float v4[4]{ rect.x, rect.y, rect.width, rect.height };
		if (ImGui::DragFloat4(p_param->getName().c_str(), v4, len * 0.01f))
		{
			p_param->set(ofRectangle(v4[0], v4[1], v4[2], v4[3]));
		}
	}

	void gf_draw_text_input(ofParameter < std::string >* p_param)
	{
		enum { MaxSizeBuf = 256 };

		char buf[MaxSizeBuf];
		strncpy(buf, p_param->get().c_str(), MaxSizeBuf);
		buf[MaxSizeBuf - 1] = '\0';
		if (ImGui::InputText(p_param->getName().c_str(), buf, MaxSizeBuf))
		{
			p_param->set(buf);
		}
	}

	char const* gf_get_gl_internal_fmt_name(int glInternalFormat) 
	{
		switch (glInternalFormat) 
		{
		case GL_RGBA:				return "GL_RGBA";
#ifndef TARGET_OPENGLES
		case GL_RGBA8:				return "GL_RGBA8";
#endif
		case GL_RGB:				return "GL_RGB";
#ifndef TARGET_OPENGLES
		case GL_RGB8:				return "GL_RGB8";
#endif
		case GL_LUMINANCE:			return "GL_LUMINANCE";
#ifndef TARGET_OPENGLES
		case GL_LUMINANCE8:			return "GL_LUMINANCE8";
		case GL_RGBA16:				return "GL_RGBA16";
		case GL_RGB16:				return "GL_RGB16";
		case GL_LUMINANCE16:		return "GL_LUMINANCE16";
		case GL_RGBA32F_ARB:		return "GL_RGBA32F_ARB";
		case GL_RGB32F_ARB:			return "GL_RGB32F_ARB";
		//added ===================================================
		//case GL_RGB32F:				return "GL_RGB32F";
		//case GL_RGBA32F:			return "GL_RGBA32F";
		//=========================================================
		case GL_LUMINANCE32F_ARB:	return "GL_LUMINANCE32F_ARB";
#endif
		case GL_LUMINANCE_ALPHA:	return "GL_LUMINANCE_ALPHA";
#ifndef TARGET_OPENGLES
		case GL_LUMINANCE8_ALPHA8:	return "GL_LUMINANCE8_ALPHA8";
		//added ===================================================
		case GL_R8:					return "GL_R8";
		case GL_R16:				return "GL_R16";
		case GL_R32F:				return "GL_R32F";
		//=========================================================
#endif
		default:					return "unknown glInternalFormat";
		}
	}

	void gf_draw_texture(ofParameter< MyTex >* p_param)
	{
		ofParameter< MyTex >& param = *p_param;
		MyTex my_tex = param.get();
		bool is_changed = false;

		ImGui::SetNextTreeNodeOpen(my_tex.is_open, ImGuiCond_Appearing);
		if (ImGui::CollapsingHeader(p_param->getName().c_str()))
		{
			ofParameter< ofTexture>& param_tex = *my_tex.sp_param_texture;
			ofTexture const& tex = param_tex.get();

			if (!tex.isAllocated())
			{
				return;
			}

			ImGui::PushID(my_tex.id);
			{
				bool yes;
				yes = !my_tex.is_fit_windows;
				if (ImGui::Checkbox("origin size", &yes))
				{
					my_tex.is_fit_windows = !yes;
					is_changed = true;
				}

				ImGui::SameLine();
				yes = my_tex.is_show_detail;
				if (ImGui::Checkbox("show detail", &yes))
				{
					my_tex.is_show_detail = yes;
					is_changed = true;
				}

				if (my_tex.is_show_detail)
				{
					ImGui::SameLine();
					ImGui::TextDisabled("w: %.2f, h: %.2f, fmt: %s", tex.getWidth(), tex.getHeight(), gf_get_gl_internal_fmt_name(tex.getTextureData().glInternalFormat));
				}
			}
			ImGui::PopID();

			float w, h;
			if (my_tex.is_fit_windows)
			{
				ImVec2 vec2win = ImGui::GetContentRegionAvail();
				float rwin = vec2win.x / vec2win.y;
				ofVec2f vec2tex(tex.getWidth(), tex.getHeight());
				float rtex = vec2tex.x / vec2tex.y;
				if (rwin < rtex)
				{
					float tmp = vec2win.x;
					w = tmp;
					tmp = tmp / tex.getWidth();
					h = tex.getHeight() * tmp;
				}
				else
				{
					float tmp = vec2win.y;
					h = tmp;
					tmp = tmp / tex.getHeight();
					w = tex.getWidth() * tmp;
				}
			}
			else
			{
				w = tex.getWidth();
				h = tex.getHeight();
			}

			ImGui::Image((ImTextureID)(uintptr_t)tex.getTextureData().textureID, ImVec2(w, h));
			if (!my_tex.is_open)
			{
				is_changed = true;
				my_tex.is_open = true;
			}
		}
		else
		{
			if (my_tex.is_open)
			{
				is_changed = true;
				my_tex.is_open = false;
			}
		}

		if (is_changed)
		{
			p_param->set(my_tex);
		}
	}

	bool gf_force_push_tag(ofxXmlSettings& xml_settings, std::string const& tag, std::string const& attri = "", std::string const& attri_val = "")
	{
		if (!xml_settings.tagExists(tag))
		{
			xml_settings.addTag(tag);
		}

		if (attri != "")
		{
			xml_settings.setAttribute(tag, attri, attri_val, 0);
		}

		return xml_settings.pushTag(tag);
	}

	template < typename PARAM_VALUE_TYPE, typename XML_VALUE_TYPE >
	void gf_save_xml_value_type(ofxXmlSettings& xml_settings, ofxImGuiParameter::ParamInfo* p_info, std::string const& tag_name)
	{
		ofParameter< ofxImGuiParameter::ValueType <PARAM_VALUE_TYPE> >& param = p_info->sp_param->cast< ofxImGuiParameter::ValueType <PARAM_VALUE_TYPE> >();
		ofxImGuiParameter::ValueType <PARAM_VALUE_TYPE> const& value_obj = param.get();
		std::string style_name;
		if (value_obj.style == ofxImGuiParameter::StyleInputField)
		{
			style_name = "InputField";
		}
		else if (value_obj.style == ofxImGuiParameter::StyleSlider)
		{
			style_name = "Slider";
		}
		else
		{
			return;
		}

		if (gf_force_push_tag(xml_settings, tag_name, "Style", style_name))
		{
			xml_settings.setValue("Value", (XML_VALUE_TYPE)value_obj.value);
			xml_settings.setValue("MinOrStep", (XML_VALUE_TYPE)value_obj.arg0);
			xml_settings.setValue("MaxOrStepFast", (XML_VALUE_TYPE)value_obj.arg1);
			xml_settings.popTag();
		}
	}

	template < typename PARAM_VALUE_TYPE, typename XML_VALUE_TYPE >
	void gf_load_xml_value_type(ofxXmlSettings& xml_settings, ofxImGuiParameter::ParamInfo* p_info, std::string const& tag_name)
	{
		ofParameter< ofxImGuiParameter::ValueType <PARAM_VALUE_TYPE> >& param = p_info->sp_param->cast< ofxImGuiParameter::ValueType <PARAM_VALUE_TYPE> >();
		ofxImGuiParameter::ValueType <PARAM_VALUE_TYPE> value_obj = param.get();
		std::string style_name;
		if (value_obj.style == ofxImGuiParameter::StyleInputField)
		{
			style_name = "InputField";
		}
		else if (value_obj.style == ofxImGuiParameter::StyleSlider)
		{
			style_name = "Slider";
		}
		else
		{
			return;
		}

		style_name = xml_settings.getAttribute(tag_name, "Style", style_name, 0);
		if (xml_settings.pushTag(tag_name))
		{
			value_obj.value = xml_settings.getValue("Value", (XML_VALUE_TYPE)value_obj.value);
			value_obj.arg0 = xml_settings.getValue("MinOrStep", (XML_VALUE_TYPE)value_obj.arg0);
			value_obj.arg1 = xml_settings.getValue("MaxOrStepFast", (XML_VALUE_TYPE)value_obj.arg1);
			xml_settings.popTag();
		}
		else
		{
			return;
		}

		std::string type_name = typeid(PARAM_VALUE_TYPE).name();

		if (style_name == "InputField")
		{
			value_obj.style = ofxImGuiParameter::StyleInputField;
			if (type_name == typeid(float).name())
			{
				p_info->func = (gf_draw_func)&gf_draw_float_input_spec;
			}
			else if (type_name == typeid(int).name())
			{
				p_info->func = (gf_draw_func)&gf_draw_int_input_spec;
			}
			else
			{
				return;
			}
		}
		else if (style_name == "Slider")
		{
			value_obj.style = ofxImGuiParameter::StyleSlider;
			if (type_name == typeid(float).name())
			{
				p_info->func = (gf_draw_func)&gf_draw_float_slider_spec;
			}
			else if (type_name == typeid(int).name())
			{
				p_info->func = (gf_draw_func)&gf_draw_int_slider_spec;
			}
			else
			{
				return;
			}
		}
		else
		{
			return;
		}

		param.set(value_obj);
	}

	ofxImGui::Gui* g_p_gui_ins = NULL;
}

std::vector< ofxImGuiParameter* >	ofxImGuiParameter::s_box;
ofEvent< void >						ofxImGuiParameter::s_event;
ofMutex								ofxImGuiParameter::s_mutex;
ofxImGuiParameter::BindedID const	ofxImGuiParameter::InvalidBindedID = 0;
ofRectangle const					ofxImGuiParameter::DefaultPosAndSize = ofRectangle(10.f, 10.f, 320.f, 640.f);

typedef ofxImGuiParameter::ParamInfo ParamInfo;
typedef ofxImGuiParameter::EnumType EnumType;

void gf_save_xml(ofxXmlSettings& xml_settings, std::vector< ParamInfo* >& container, gf_draw_func i_func, gf_draw_func f_func);
void gf_load_xml(ofxXmlSettings& xml_settings, std::vector< ParamInfo* >& container, gf_draw_func i_func, gf_draw_func f_func);

namespace
{
	bool gf_check_ext(std::string const& ext, std::vector<std::string> const& box_ext)
	{
		if (box_ext.empty())
		{
			return true;
		}

		for (size_t i = 0; i < box_ext.size(); ++i)
		{
			if (ext == box_ext[i])
			{
				return true;
			}
		}

		return false;
	}

	void gf_split(std::vector<std::string>* p_out, std::string const& str, std::string const& token)
	{
		const char *sep = token.c_str();
		char* s = new char[str.length() + 1];
		strncpy(s, str.c_str(), str.length());
		s[str.length()] = '\0';

		char* pch = strtok(s, sep);
		while (pch)
		{
			p_out->push_back(pch);
			pch = strtok(NULL, sep);
		}

		delete[] s;
	}
}

//static ===============================================
bool ofxImGuiParameter::GetEnumTypeFormDirectory(EnumType* p_out, std::string const& in_path, std::string const& ext_filter)
{
	if (!p_out)
	{
		return false;
	}

	ofFile file;
	if (!file.open(in_path))
	{
		return false;
	}

	if (file.isDirectory())
	{
		ofDirectory dir(file);
		size_t size = dir.listDir();
		std::vector<std::string> box_ext;
		gf_split(&box_ext, ext_filter, " ");

		for (size_t i = 0; i < size; ++i)
		{
			ofFile file_child = dir[i];

			if (file_child.isFile())
			{
				if (!gf_check_ext(file_child.getExtension(), box_ext))
				{
					continue;
				}

				p_out->content.push_back(in_path + "/" + file_child.getFileName());
			}
		}

		dir.close();
	}
	file.close();
	return true;
}

void ofxImGuiParameter::Initialize()
{
	ofScopedLock locker_s(s_mutex);
	if (!g_p_gui_ins)
	{
		g_p_gui_ins = new ofxImGui::Gui();
	}

	g_p_gui_ins->setup();
}

void ofxImGuiParameter::Finalize()
{
	ofScopedLock locker_s(s_mutex);
	for (size_t i = 0; i < s_box.size(); ++i)
	{
		s_box[i]->mf_exit();
	}

	if (g_p_gui_ins)
	{
		delete g_p_gui_ins;
		g_p_gui_ins = NULL;
	}
}

void ofxImGuiParameter::Draw()
{
	ofScopedLock locker_s(s_mutex);
	if (!g_p_gui_ins)
	{
		return;
	}

	g_p_gui_ins->begin();

	ofNotifyEvent(s_event, g_p_gui_ins);
		
	for (size_t i = 0; i < s_box.size(); ++i)
	{
		s_box[i]->draw();
	}

	g_p_gui_ins->end();
}

ofEvent< void >& ofxImGuiParameter::GetOnDrawEvent()
{
	return s_event;
}

/////////////////////////////////////////////////////////////////////////////

ofxImGuiParameter::ofxImGuiParameter()
: m_show_dialog(0)
, m_is_visible(true)
, m_is_setup(false)
, m_is_locked_shortcut(false)
, m_is_enable_dialog(true)
, m_is_dialog_auto_gone(true)
{}


ofxImGuiParameter::~ofxImGuiParameter()
{
	exit();
}

bool ofxImGuiParameter::setup(std::string const& title, ofRectangle const& rect, Style default_style)
{
	return mf_setup(title, rect, default_style);
}

bool ofxImGuiParameter::setup(std::string const& title, Style default_style)
{
	return mf_setup(title, DefaultPosAndSize, default_style);
}

bool ofxImGuiParameter::is_setup()
{
	ofScopedLock locker(m_mutex);
	return m_is_setup;
}

void ofxImGuiParameter::exit()
{
	{
		ofScopedLock lockerS(s_mutex);

		{
			ofScopedLock locker(m_mutex);
			mf_exit();
		}
	}
}

bool ofxImGuiParameter::mf_setup(std::string const& title, ofRectangle const& rect, Style default_style)
{
	{
		ofScopedLock locker_s(s_mutex);

		{
			ofScopedLock locker(m_mutex);

			m_title = title;

			if (m_xml_filepath == "")
			{
				m_xml_filepath = m_title + ".xml";
			}

			m_pos_and_size = rect;
			ImGui::GetIO().MouseDrawCursor = false;
			if (m_is_setup)
			{
				return true;
			}

			s_box.push_back(this);

			ofAddListener(ofEvents().keyPressed, this, &ofxImGuiParameter::mf_on_key_pressed);
			//ofAddListener(ofEvents().keyReleased, this, &ofxImGuiParameter::mf_on_key_released);

			switch (default_style)
			{
			default:
			case StyleSlider:
				m_default_draw_i_func = (gf_draw_func)&gf_draw_int_slider_default;
				m_default_draw_f_func = (gf_draw_func)&gf_draw_float_slider_default;
				break;

			case StyleDrag:
				m_default_draw_i_func = (gf_draw_func)&gf_draw_int_drag_default;
				m_default_draw_f_func = (gf_draw_func)&gf_draw_float_drag_default;
				break;

			case StyleInputField:
				m_default_draw_i_func = (gf_draw_func)&gf_draw_int_input_default;
				m_default_draw_f_func = (gf_draw_func)&gf_draw_float_input_default;
				break;
			}

			m_is_setup = true;
			return true;
		}
	}
}

void ofxImGuiParameter::mf_exit()
{
	if (!m_is_setup)
	{
		return;
	}

	//ofRemoveListener(ofEvents().keyReleased, this, &ofxImGuiParameter::mf_on_key_released);
	ofRemoveListener(ofEvents().keyPressed, this, &ofxImGuiParameter::mf_on_key_pressed);

	for (size_t i = 0; i < s_box.size(); ++i)
	{
		if (s_box[i] == this)
		{
			size_t last_index = s_box.size() - 1;
			if (i != last_index)
			{
				s_box[i] = s_box[last_index];
			}
			s_box.pop_back();
			break;
		}
	}

	mf_unbind(m_parameters);
	m_is_setup = false;
}

ofxImGuiParameter::BindedID ofxImGuiParameter::bind(ofAbstractParameter const& param)
{
	return mf_bind(param, m_parameters);
}

void ofxImGuiParameter::unbind(BindedID id)
{
	mf_unbind(id ,m_parameters);
}

void ofxImGuiParameter::draw()
{
	if (m_show_dialog)
	{
		mf_draw_dialog();
	}

	if (!m_is_visible)
	{
		return;
	}

	do
	{
		ImGui::SetNextWindowPos(ImVec2(m_pos_and_size.getX(), m_pos_and_size.getY()), ImGuiCond_Appearing);
		ImGui::SetNextWindowSize(ImVec2(m_pos_and_size.getWidth(), m_pos_and_size.getHeight()), ImGuiCond_Appearing);

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_HorizontalScrollbar;
		if (!ImGui::Begin(m_title.c_str(), NULL, window_flags))
		{
			break;
		}

		ImVec2 pos = ImGui::GetWindowPos();
		ImVec2 size = ImGui::GetWindowSize();

		m_pos_and_size.x = pos.x;
		m_pos_and_size.y = pos.y;
		m_pos_and_size.width = size.x;
		m_pos_and_size.height = size.y;

		m_is_focused = ImGui::IsWindowFocused();

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save", "Ctrl+S"))
				{
					mf_internal_save();
				}

				if (ImGui::MenuItem("Load", "Ctrl+L"))
				{
					mf_internal_load();
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Option"))
			{
				{
					bool is_hidden = !m_is_visible;
					ImGui::MenuItem("Hidden", "Crtl+H", &is_hidden);
					m_is_visible = !is_hidden;
				}

				ImGui::MenuItem("Lock Shortcut", "", &m_is_locked_shortcut);
				ImGui::MenuItem("Enable Message", "", &m_is_enable_dialog);
				if (m_is_enable_dialog)
				{
					ImGui::MenuItem("Message Auto Gone", "", &m_is_dialog_auto_gone);
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ofNotifyEvent(m_pre_draw_event, this);

		for (size_t i = 0; i < m_parameters.size(); ++i)
		{
			ImGui::PushID((int)i);
			sf_draw(m_parameters[i]);
			ImGui::PopID();
		}

		ofNotifyEvent(m_post_draw_event, this);

	} while (0);

	ImGui::End();
}

bool ofxImGuiParameter::save(std::string const& filepath)
{
	std::string xml_filepath = filepath;
	if (xml_filepath == "")
	{
		xml_filepath = m_xml_filepath;
	}

	xml_filepath = ofToDataPath(xml_filepath);

	ofxXmlSettings xml_settings;
	bool yes = xml_settings.load(xml_filepath);

	if (gf_force_push_tag(xml_settings, "ofxImGuiParameter"))
	{
		if (gf_force_push_tag(xml_settings, "Settings4ofxImGuiParameter"))
		{
			if (gf_force_push_tag(xml_settings, "PosAndSize"))
			{
				xml_settings.setValue("X", (int)m_pos_and_size.getX());
				xml_settings.setValue("Y", (int)m_pos_and_size.getY());
				xml_settings.setValue("Width", (int)m_pos_and_size.getWidth());
				xml_settings.setValue("Height", (int)m_pos_and_size.getHeight());
				xml_settings.popTag();
			}

			xml_settings.setValue("IsLockedShortcut", m_is_locked_shortcut ? "true" : "false");
			xml_settings.setValue("IsHidden", m_is_visible ? "false" : "true");
			xml_settings.setValue("IsEnableMessage", m_is_enable_dialog ? "true" : "false");
			xml_settings.setValue("IsMessageAutoGone", m_is_dialog_auto_gone ? "true" : "false");
			xml_settings.popTag();
		}

		gf_save_xml(xml_settings, m_parameters, m_default_draw_i_func, m_default_draw_f_func);
		xml_settings.popTag();
	}

	ofLogNotice("ofxImGuiParameter", "Save %s to %s", m_title.c_str(), xml_filepath.c_str());
	return xml_settings.save(xml_filepath);
}

bool ofxImGuiParameter::load(std::string const& filepath)
{
	std::string xml_filepath = filepath;
	if (xml_filepath == "")
	{
		xml_filepath = m_xml_filepath;
	}

	xml_filepath = ofToDataPath(xml_filepath);
	ofxXmlSettings xml_settings;
	if (!xml_settings.load(xml_filepath))
	{
		return false;
	}

	if (!xml_settings.pushTag("ofxImGuiParameter"))
	{
		return false;
	}

	if (xml_settings.pushTag("Settings4ofxImGuiParameter"))
	{
		if (xml_settings.pushTag("PosAndSize"))
		{
			m_pos_and_size.x = xml_settings.getValue("X", (int)m_pos_and_size.getX());
			m_pos_and_size.y = xml_settings.getValue("Y", (int)m_pos_and_size.getY());
			m_pos_and_size.width = xml_settings.getValue("Width", (int)m_pos_and_size.getWidth());
			m_pos_and_size.height = xml_settings.getValue("Height", (int)m_pos_and_size.getHeight());
			xml_settings.popTag();
		}

		std::string value;
		value = xml_settings.getValue("IsLockedShortcut", m_is_locked_shortcut ? "true" : "false");
		m_is_locked_shortcut = value == "true";

		value = xml_settings.getValue("IsHidden", m_is_visible ? "false" : "true");
		m_is_visible = value != "true";

		value = xml_settings.getValue("IsEnableMessage", m_is_enable_dialog ? "true" : "false");
		m_is_enable_dialog = value == "true";

		value = xml_settings.getValue("IsMessageAutoGone", m_is_dialog_auto_gone ? "true" : "false");
		m_is_dialog_auto_gone = value == "true";

		xml_settings.popTag();
	}

	gf_load_xml(xml_settings, m_parameters, m_default_draw_i_func, m_default_draw_f_func);

	xml_settings.popTag();

	ofLogNotice("ofxImGuiParameter", "Load %s from %s", m_title.c_str(), xml_filepath.c_str());
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ofxImGuiParameter::sf_draw(ParamInfo* p_param_info)
{
	ImGui::Indent(8.f);
	if (p_param_info->func)
	{
		p_param_info->func(p_param_info->sp_param.get());
	}
	else //Group
	{
		bool is_open = p_param_info->arg;

		ImGui::SetNextTreeNodeOpen(is_open, ImGuiCond_Appearing);
		if (ImGui::CollapsingHeader(p_param_info->sp_param->getName().c_str()))
		{
			for (size_t i = 0; i < p_param_info->children.size(); ++i)
			{
				ImGui::PushID((int)i);
				sf_draw(p_param_info->children[i]);
				ImGui::PopID();
			}
			p_param_info->arg = 1;
		}
		else
		{
			p_param_info->arg = 0;
		}
	}
	ImGui::Unindent(8.f);
}

void ofxImGuiParameter::mf_draw_dialog()
{
	ImGuiWindowFlags window_flags =
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoScrollWithMouse |
		ImGuiWindowFlags_NoScrollbar;

	enum
	{
		DefaultWidthOfDialog = 160,
		DefaultHeightOfDialog = 30,

		WGapLeft = 5,
		HGapRight = 5,
		HGap0 = 3,
		HGap1 = 5,
		HGap2 = 50,
	};

	ImVec2 size_of_title = ImGui::CalcTextSize(m_title_of_dialog.c_str());
	ImVec2 size_of_message = ImGui::CalcTextSize(m_msg_of_dialog.c_str());
	ImVec2 size_of_confirm;
	if (m_is_dialog_auto_gone)
	{
		--m_show_dialog;

		size_of_confirm.x = 0.f;
		size_of_confirm.y = 0.f;
	}
	else
	{
		size_of_confirm = ImGui::CalcTextSize("Confirm");
		//size_of_confirm.y += 10;
	}

	size_t width_of_dialog = std::max< size_t >(DefaultWidthOfDialog, size_of_message.x + WGapLeft + HGapRight);
	width_of_dialog = std::max< size_t >(width_of_dialog, size_of_title.x + WGapLeft + HGapRight);

	size_t height_of_dialog = std::max< size_t >(DefaultHeightOfDialog, size_of_message.y + HGap0 + HGap1 + HGap2 + size_of_confirm.y);
	size_t wgap_of_message = (width_of_dialog - (size_t)(size_of_message.x)) >> 1;

	size_t wgap_of_confirm;
	if (m_is_dialog_auto_gone)
	{
		wgap_of_confirm = 0;
	}
	else
	{
		wgap_of_confirm = (width_of_dialog - (size_t)(size_of_confirm.x)) >> 1;
	}

	ImGui::SetNextWindowPos(ImVec2((ofGetWidth() - width_of_dialog) >> 1, (ofGetHeight() - height_of_dialog) >> 1), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(width_of_dialog, height_of_dialog), ImGuiCond_Always);

	if (ImGui::Begin(m_title_of_dialog.c_str(), NULL, window_flags))
	{
		ImGui::Dummy(ImVec2(HGap0, HGap0));
		ImGui::NewLine(); ImGui::SameLine(wgap_of_message);
		ImGui::Text(m_msg_of_dialog.c_str());

		if (!m_is_dialog_auto_gone)
		{
			ImGui::Dummy(ImVec2(HGap1, HGap1));
			ImGui::NewLine(); ImGui::SameLine(wgap_of_confirm);
			if (ImGui::Button("Confirm"))
			{
				m_show_dialog = 0;
			}
		}
	}
	ImGui::End();	
}

bool gf_is_bad_char(char c)
{
	if (c < '0') 
		return true;

	if (c > '9')
	{
		if (c < 'A') 
			return true;

		if (c > 'Z')
		{
			if (c < 'a')
				return true;

			if (c > 'z')
				return true;
		}
	}
	return false;
}

void gf_remove_any_bad_char(std::string& str)
{
	std::replace_if(str.begin(), str.end(), std::bind(&gf_is_bad_char, std::placeholders::_1), '_');
	//std::replace(str.begin(), str.end(), ' ', '_');
	//std::replace(str.begin(), str.end(), '(', '_');
	//std::replace(str.begin(), str.end(), ')', '_');
	//std::replace(str.begin(), str.end(), ':', '_');
	//std::replace(str.begin(), str.end(), '<', '_');
	//std::replace(str.begin(), str.end(), '>', '_');
	//std::replace(str.begin(), str.end(), '[', '_');
	//std::replace(str.begin(), str.end(), ']', '_');
	//std::replace(str.begin(), str.end(), '{', '_');
	//std::replace(str.begin(), str.end(), '}', '_');
	//std::replace(str.begin(), str.end(), '-', '_');
	//std::replace(str.begin(), str.end(), '\\', '_');
	//std::replace(str.begin(), str.end(), '/', '_');
	//std::replace(str.begin(), str.end(), '!', '_');
	//std::replace(str.begin(), str.end(), '?', '_');
}

void gf_save_xml(ofxXmlSettings& xml_settings, std::vector< ParamInfo* >& container, gf_draw_func i_func, gf_draw_func f_func)
{
	for (size_t i = 0; i < container.size(); ++i)
	{
		ParamInfo* p_info = container[i];
		std::string tag_name = p_info->sp_param->getName();
		gf_remove_any_bad_char(tag_name);

		if (p_info->func == NULL)
		{
			if (gf_force_push_tag(xml_settings, tag_name, "IsOpen", p_info->arg ? "true" : "false"))
			{
				gf_save_xml(xml_settings, p_info->children, i_func, f_func);
				xml_settings.popTag();
			}
		}
		else
		{
			if (p_info->func == (gf_draw_func)&gf_draw_bool)
			{
				xml_settings.setValue(tag_name, p_info->sp_param->cast<bool>().get() ? "true" : "false");
			}
			else if (p_info->func == f_func)
			{
				xml_settings.setValue(tag_name, (double)p_info->sp_param->cast<float>().get());
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_float_input_spec || p_info->func == (gf_draw_func)&gf_draw_float_slider_spec)
			{
				gf_save_xml_value_type <float, double>(xml_settings, p_info, tag_name);
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_int_input_spec || p_info->func == (gf_draw_func)&gf_draw_int_slider_spec)
			{
				gf_save_xml_value_type <int, int>(xml_settings, p_info, tag_name);
			}
			else if (p_info->func == i_func)
			{
				xml_settings.setValue(tag_name, p_info->sp_param->cast<int>().get());
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_color_u8)
			{
				ofColor const& color = p_info->sp_param->cast<ofColor>().get();
				if (gf_force_push_tag(xml_settings, tag_name, "PixelType", "U8"))
				{	
					xml_settings.setValue("R", (int)color.r);
					xml_settings.setValue("G", (int)color.g);
					xml_settings.setValue("B", (int)color.b);
					xml_settings.setValue("A", (int)color.a);
					xml_settings.popTag();
				}				
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_color_f32)
			{
				ofFloatColor const& color = p_info->sp_param->cast<ofFloatColor>().get();
				if (gf_force_push_tag(xml_settings, tag_name, "PixelType", "F32"))
				{
					xml_settings.setValue("R", (double)color.r);
					xml_settings.setValue("G", (double)color.g);
					xml_settings.setValue("B", (double)color.b);
					xml_settings.setValue("A", (double)color.a);
					xml_settings.popTag();
				}
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_enum)
			{
				ofParameter< EnumType >& param = p_info->sp_param->cast< EnumType >();
				EnumType const& e_value = param.get();

				int select = 0;
				if (e_value.select < e_value.content.size() && e_value.select > 0)
				{
					select = e_value.select;
				}
				else  if (e_value.content.empty())
				{
					select = -1;
				}

				xml_settings.setValue(tag_name, select < 0 ? "" : e_value.content[select]);
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_vec2f)
			{
				ofVec2f const& vec2f = p_info->sp_param->cast<ofVec2f>().get();
				if (gf_force_push_tag(xml_settings, tag_name))
				{
					xml_settings.setValue("X", (double)vec2f.x);
					xml_settings.setValue("Y", (double)vec2f.y);
					xml_settings.popTag();
				}
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_vec3f)
			{
				ofVec3f const& vec3f = p_info->sp_param->cast<ofVec3f>().get();
				if (gf_force_push_tag(xml_settings, tag_name))
				{
					xml_settings.setValue("X", (double)vec3f.x);
					xml_settings.setValue("Y", (double)vec3f.y);
					xml_settings.setValue("Z", (double)vec3f.z);
					xml_settings.popTag();
				}
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_vec4f)
			{
				ofVec4f const& vec4f = p_info->sp_param->cast<ofVec4f>().get();
				if (gf_force_push_tag(xml_settings, tag_name))
				{
					xml_settings.setValue("X", (double)vec4f.x);
					xml_settings.setValue("Y", (double)vec4f.y);
					xml_settings.setValue("Z", (double)vec4f.z);
					xml_settings.setValue("W", (double)vec4f.w);
					xml_settings.popTag();
				}
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_rect)
			{
				ofRectangle const& rect = p_info->sp_param->cast<ofRectangle>().get();
				if (gf_force_push_tag(xml_settings, tag_name))
				{
					xml_settings.setValue("X", (double)rect.x);
					xml_settings.setValue("Y", (double)rect.y);
					xml_settings.setValue("Width", (double)rect.width);
					xml_settings.setValue("Height", (double)rect.height);
					xml_settings.popTag();
				}
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_text_input)
			{
				xml_settings.setValue(tag_name, p_info->sp_param->cast<std::string>().get());
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_texture)
			{
				MyTex const& my_tex = p_info->sp_param->cast<MyTex>().get();
				tag_name = my_tex.sp_param_texture->getName();

				if (gf_force_push_tag(xml_settings, tag_name, "IsOpen", my_tex.is_open ? "true" : "false"))
				{
					xml_settings.setValue("IsOriginSize", !my_tex.is_fit_windows ? "true" : "false");
					xml_settings.setValue("IsShowDetail", my_tex.is_show_detail ? "true" : "false");
					xml_settings.popTag();
				}
			}
		}
	}
}

void gf_load_xml(ofxXmlSettings& xml_settings, std::vector< ParamInfo* >& container, gf_draw_func i_func, gf_draw_func f_func)
{
	for (size_t i = 0; i < container.size(); ++i)
	{
		ParamInfo* p_info = container[i];
		std::string tag_name = p_info->sp_param->getName();
		gf_remove_any_bad_char(tag_name);

		if (p_info->func == NULL)
		{
			std::string value = xml_settings.getAttribute(tag_name, "IsOpen", p_info->arg ? "true" : "false", 0);
			if (value == "true")
			{
				p_info->arg = 1;
			}
			else
			{
				p_info->arg = 0;
			}

			if (xml_settings.pushTag(tag_name))
			{
				gf_load_xml(xml_settings, p_info->children, i_func, f_func);
				xml_settings.popTag();
			}
		}
		else
		{
			if (p_info->func == (gf_draw_func)&gf_draw_bool)
			{
				ofParameter<bool>& param_b = p_info->sp_param->cast<bool>();
				std::string value = xml_settings.getValue(tag_name, param_b.get() ? "true" : "false");
				param_b.set(value == "true");
			}
			else if (p_info->func == f_func)
			{
				ofParameter<float>& param_f = p_info->sp_param->cast<float>();
				double value = xml_settings.getValue(tag_name, (double)param_f.get());
				param_f.set(static_cast<float>(value));
			}
			else if (p_info->func == i_func)
			{
				ofParameter<int>& param_i = p_info->sp_param->cast<int>();
				int value = xml_settings.getValue(tag_name, param_i.get());
				param_i.set(value);
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_float_input_spec || p_info->func == (gf_draw_func)&gf_draw_float_slider_spec)
			{
				gf_load_xml_value_type <float, double>(xml_settings, p_info, tag_name);
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_int_input_spec || p_info->func == (gf_draw_func)&gf_draw_int_slider_spec)
			{
				gf_load_xml_value_type <int, int>(xml_settings, p_info, tag_name);
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_color_u8)
			{
				ofParameter< ofColor >& param_color = p_info->sp_param->cast< ofColor >();
				ofColor color = param_color.get();

				std::string pixel_type = xml_settings.getAttribute(tag_name, "PixelType", "U8", 0);

				if (xml_settings.pushTag(tag_name))
				{
					do 
					{
						if (pixel_type == "U8")
						{
							color.r = static_cast<unsigned char>(ofClamp(xml_settings.getValue("R", (int)color.r), 0, 255));
							color.g = static_cast<unsigned char>(ofClamp(xml_settings.getValue("G", (int)color.g), 0, 255));
							color.b = static_cast<unsigned char>(ofClamp(xml_settings.getValue("B", (int)color.b), 0, 255));
							color.a = static_cast<unsigned char>(ofClamp(xml_settings.getValue("A", (int)color.a), 0, 255));
						}
						else if (pixel_type == "F32")
						{
							color.r = static_cast<unsigned char>(ofClamp(xml_settings.getValue("R", (double)(color.r / 255.0)), 0.0, 1.0) * 255);
							color.g = static_cast<unsigned char>(ofClamp(xml_settings.getValue("G", (double)(color.g / 255.0)), 0.0, 1.0) * 255);
							color.b = static_cast<unsigned char>(ofClamp(xml_settings.getValue("B", (double)(color.b / 255.0)), 0.0, 1.0) * 255);
							color.a = static_cast<unsigned char>(ofClamp(xml_settings.getValue("A", (double)(color.a / 255.0)), 0.0, 1.0) * 255);
						}
						else
						{
							break;
						}

						param_color.set(color);

					} while (0);

					xml_settings.popTag();
				}
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_color_f32)
			{
				ofParameter< ofFloatColor >& param_color = p_info->sp_param->cast< ofFloatColor >();
				ofFloatColor color = param_color.get();

				std::string pixel_type = xml_settings.getAttribute(tag_name, "PixelType", "F32", 0);

				if (xml_settings.pushTag(tag_name))
				{
					do
					{
						if (pixel_type == "U8")
						{
							color.r = xml_settings.getValue("R", (int)color.r) / 255.f;
							color.g = xml_settings.getValue("G", (int)color.g) / 255.f;
							color.b = xml_settings.getValue("B", (int)color.b) / 255.f;
							color.a = xml_settings.getValue("A", (int)color.a) / 255.f;
						}
						else if (pixel_type == "F32")
						{
							color.r = static_cast<float>(xml_settings.getValue("R", (double)color.r));
							color.g = static_cast<float>(xml_settings.getValue("G", (double)color.g));
							color.b = static_cast<float>(xml_settings.getValue("B", (double)color.b));
							color.a = static_cast<float>(xml_settings.getValue("A", (double)color.a));
						}
						else
						{
							break;
						}

						param_color.set(color);

					} while (0);

					xml_settings.popTag();
				}
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_enum)
			{
				ofParameter< EnumType >& param_e = p_info->sp_param->cast< EnumType >();
				EnumType e_value = param_e.get();
				std::string value = xml_settings.getValue(tag_name, "");
				int select = -1;

				for (size_t i = 0; i < e_value.content.size(); ++i)
				{
					if (e_value.content[i] == value)
					{
						select = (int)i;
						break;
					}
				}

				if (select >= 0)
				{
					e_value.select = select;
					param_e.set(e_value);
				}
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_vec2f)
			{
				ofParameter< ofVec2f >& param_vec2f = p_info->sp_param->cast< ofVec2f >();
				ofVec2f vec2f = param_vec2f.get();

				if (xml_settings.pushTag(tag_name))
				{
					vec2f.x = (float)xml_settings.getValue("X", (double)vec2f.x);
					vec2f.y = (float)xml_settings.getValue("Y", (double)vec2f.y);
					param_vec2f.set(vec2f);
					xml_settings.popTag();
				}
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_vec3f)
			{
				ofParameter< ofVec3f >& param_vec3f = p_info->sp_param->cast< ofVec3f >();
				ofVec3f vec3f = param_vec3f.get();

				if (xml_settings.pushTag(tag_name))
				{
					vec3f.x = (float)xml_settings.getValue("X", (double)vec3f.x);
					vec3f.y = (float)xml_settings.getValue("Y", (double)vec3f.y);
					vec3f.z = (float)xml_settings.getValue("Z", (double)vec3f.z);
					param_vec3f.set(vec3f);
					xml_settings.popTag();
				}
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_vec4f)
			{
				ofParameter< ofVec4f >& param_vec4f = p_info->sp_param->cast< ofVec4f >();
				ofVec4f vec4f = param_vec4f.get();

				if (xml_settings.pushTag(tag_name))
				{
					vec4f.x = (float)xml_settings.getValue("X", (double)vec4f.x);
					vec4f.y = (float)xml_settings.getValue("Y", (double)vec4f.y);
					vec4f.z = (float)xml_settings.getValue("Z", (double)vec4f.z);
					vec4f.w = (float)xml_settings.getValue("W", (double)vec4f.w);
					param_vec4f.set(vec4f);
					xml_settings.popTag();
				}
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_rect)
			{
				ofParameter< ofRectangle >& param_rect = p_info->sp_param->cast< ofRectangle >();
				ofRectangle rect = param_rect.get();

				if (xml_settings.pushTag(tag_name))
				{
					rect.x = (float)xml_settings.getValue("X", (double)rect.x);
					rect.y = (float)xml_settings.getValue("Y", (double)rect.y);
					rect.width = (float)xml_settings.getValue("Width", (double)rect.width);
					rect.height = (float)xml_settings.getValue("Height", (double)rect.height);
					param_rect.set(rect);
					xml_settings.popTag();
				}
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_text_input)
			{
				ofParameter<std::string>& param_str = p_info->sp_param->cast<std::string>();
				param_str.set(xml_settings.getValue(tag_name, param_str.get()));
			}
			else if (p_info->func == (gf_draw_func)&gf_draw_texture)
			{
				ofParameter<MyTex>& param_my_tex = p_info->sp_param->cast<MyTex>();
				MyTex my_tex = param_my_tex.get();
				tag_name = my_tex.sp_param_texture->getName();

				std::string value = xml_settings.getAttribute(tag_name, "IsOpen", my_tex.is_open ? "true" : "false", 0);
				my_tex.is_open = (value == "true");

				if (xml_settings.pushTag(tag_name))
				{
					value = xml_settings.getValue("IsOriginSize", !my_tex.is_fit_windows ? "true" : "false");
					my_tex.is_fit_windows = (value != "true");

					value = xml_settings.getValue("IsShowDetail", my_tex.is_show_detail ? "true" : "false");
					my_tex.is_show_detail = (value == "true");
					xml_settings.popTag();
				}
				param_my_tex.set(my_tex);
			}
		}

	}
}

ofxImGuiParameter::BindedID ofxImGuiParameter::mf_bind(ofAbstractParameter const& param, std::vector< ParamInfo* >& contanier)
{
	ParamInfo* p_info = new ParamInfo();
	shared_ptr<ofAbstractParameter> sp_param = param.newReference();
	std::string type_name = param.type();
	if (type_name == typeid(ofParameterGroup).name())
	{
		p_info->func = NULL;
		ofParameterGroup const& group = (ofParameterGroup const&)param;
		for (size_t i = 0; i < group.size(); ++i)
		{
			mf_bind(group[i], p_info->children);
		}
	}
	else if (type_name == typeid(ofParameter<bool>).name())
	{
		p_info->func = (gf_draw_func)&gf_draw_bool;
	}
	else if (type_name == typeid(ofParameter<int>).name())
	{
		p_info->func = m_default_draw_i_func;
	}
	else if (type_name == typeid(ofParameter<float>).name())
	{
		p_info->func = m_default_draw_f_func;
	}
	else if (type_name == typeid(ofParameter<EnumType>).name())
	{
		p_info->func = (gf_draw_func)&gf_draw_enum;
	}
	else if (type_name == typeid(ofParameter<ofVec2f>).name())
	{
		p_info->func = (gf_draw_func)&gf_draw_vec2f;
	}
	else if (type_name == typeid(ofParameter<ofVec3f>).name())
	{
		p_info->func = (gf_draw_func)&gf_draw_vec3f;
	}
	else if (type_name == typeid(ofParameter<ofVec4f>).name())
	{
		p_info->func = (gf_draw_func)&gf_draw_vec4f;
	}
	else if (type_name == typeid(ofParameter<ofRectangle>).name())
	{
		p_info->func = (gf_draw_func)&gf_draw_rect;
	}
	else if (type_name == typeid(ofParameter< ValueType < float > >).name())
	{
		ofParameter< ValueType < float > >& param_val_f = sp_param->cast< ValueType < float > >();
		switch (param_val_f.get().style)
		{
		case StyleSlider:		p_info->func = (gf_draw_func)&gf_draw_float_slider_spec;	break;
		case StyleInputField:	p_info->func = (gf_draw_func)&gf_draw_float_input_spec;	break;
		case StyleDrag:			p_info->func = (gf_draw_func)&gf_draw_float_drag_spec;	break;
		default:
			delete p_info;
			return InvalidBindedID;
		}
	}
	else if (type_name == typeid(ofParameter< ofColor >).name())
	{
		p_info->func = (gf_draw_func)&gf_draw_color_u8;
	}
	else if (type_name == typeid(ofParameter< ofFloatColor >).name())
	{
		p_info->func = (gf_draw_func)&gf_draw_color_f32;
	}
	else if (type_name == typeid(ofParameter< ValueType < int > >).name())
	{
		ofParameter< ValueType < float > >& param_val_i = sp_param->cast< ValueType < float > >();
		switch (param_val_i.get().style)
		{
		case StyleSlider:		p_info->func = (gf_draw_func)&gf_draw_int_slider_spec;	break;
		case StyleInputField:	p_info->func = (gf_draw_func)&gf_draw_int_input_spec;	break;
		case StyleDrag:			p_info->func = (gf_draw_func)&gf_draw_int_drag_spec;		break;
		default:
			delete p_info;
			return InvalidBindedID;
		}
	}
	else if (type_name == typeid(ofParameter< std::string >).name())
	{
		p_info->func = (gf_draw_func)&gf_draw_text_input;
	}
	else if (type_name == typeid(ofParameter< ofTexture >).name())
	{
		ofParameter< ofTexture > const& param_tex = (ofParameter< ofTexture > const&) param;
		sp_parm_my_tex sp_temp = sp_parm_my_tex(new ofParameter< MyTex >());
		
		MyTex my_tex;
		my_tex.sp_param_texture = std::make_shared< ofParameter< ofTexture > >(param_tex);
		my_tex.is_fit_windows = true;
		my_tex.is_show_detail = false;
		my_tex.id = static_cast<uint32_t>(ofGetElapsedTimeMillis());
		(*sp_temp).set(std::string("[ofTexture]: ") + param.getName() ,my_tex);

		sp_param = sp_temp;
		p_info->func = (gf_draw_func)&gf_draw_texture;
	}
	else
	{
		delete p_info;
		return InvalidBindedID;
	}

	p_info->sp_param = sp_param;
	p_info->arg = 0;
	contanier.push_back(p_info);
	return reinterpret_cast<BindedID>(p_info);
}

void ofxImGuiParameter::mf_unbind(std::vector< ParamInfo* >& contanier)
{
	while (!contanier.empty())
	{
		ParamInfo* p_info = contanier.back();
		mf_unbind(p_info->children);
		p_info->sp_param = nullptr;
		delete p_info;
		contanier.pop_back();
	}
}

void ofxImGuiParameter::mf_unbind(BindedID bid, std::vector< ParamInfo* >& contanier)
{
	typedef std::vector< ParamInfo* >::iterator iterator;
	for (iterator iter = contanier.begin(); iter != contanier.end(); ++iter)
	{
		ParamInfo* p_info = *iter;
		if (reinterpret_cast<BindedID>(p_info) != bid)
		{
			continue;
		}

		mf_unbind(p_info->children);
		p_info->sp_param = nullptr;
		delete p_info;
		contanier.erase(iter);
		return;
	}
}

void ofxImGuiParameter::mf_show_dialog(std::string const& tittle, std::string const& message)
{
	if (!m_is_enable_dialog)
	{
		return;
	}

	m_title_of_dialog = m_title + "::" + tittle;
	m_msg_of_dialog = message;
	m_show_dialog = static_cast<size_t>((ofGetFrameRate() * 5) / 10);
}

void ofxImGuiParameter::mf_internal_save()
{
	bool yes = save();
	if (yes)
	{
		mf_show_dialog("Info", "Save Success");
	}
	else
	{
		mf_show_dialog("Error", "Save Failed");
	}
}

void ofxImGuiParameter::mf_internal_load()
{
	bool yes = load();
	if (yes)
	{
		mf_show_dialog("Info", "Load Success");
	}
	else
	{
		mf_show_dialog("Error", "Load Failed");
	}
}

void ofxImGuiParameter::mf_check_and_exe_general_shortcut(ofKeyEventArgs& arg)
{
	switch (arg.keycode)
	{
	case 'S':
	case 's':
		if (ofGetKeyPressed(OF_KEY_CONTROL))
		{
			mf_internal_save();
		}
		break;

	case 'L':
	case 'l':
		if (ofGetKeyPressed(OF_KEY_CONTROL))
		{
			mf_internal_load();
		}
		break;
	case 'H':
	case 'h':
		if (ofGetKeyPressed(OF_KEY_CONTROL))
		{
			m_is_visible = !m_is_visible;
		}
		break;

	}
}

void ofxImGuiParameter::mf_on_key_pressed(ofKeyEventArgs& arg)
{
	if ((m_is_locked_shortcut || !m_is_visible || !m_is_focused) && !mf_is_force_to_use_shortcut())
	{
		return;
	}

	mf_check_and_exe_general_shortcut(arg);
}

//void ofxImGuiParameter::mf_on_key_released(ofKeyEventArgs& arg){}

bool ofxImGuiParameter::mf_is_force_to_use_shortcut()
{
	return (ofGetKeyPressed(OF_KEY_ALT) && ofGetKeyPressed(OF_KEY_SHIFT));
}
