#pragma once

#include <vector>

#include "drmobject.h"

namespace kms
{

struct ConnectorPriv;

struct Videomode
{
	uint32_t clock;
	uint16_t hdisplay, hsync_start, hsync_end, htotal, hskew;
	uint16_t vdisplay, vsync_start, vsync_end, vtotal, vscan;

	uint32_t vrefresh;

	uint32_t flags;
	uint32_t type;
	char name[32]; // XXX
};

class Connector : public DrmObject
{
	friend class Card;
public:
	void print_short() const;

	Videomode get_default_mode() const;

	Videomode get_mode(const std::string& mode) const;

	Crtc* get_current_crtc() const;
	std::vector<Crtc*> get_possible_crtcs() const;

	bool connected() const;

	const std::string& fullname() const { return m_fullname; }
	uint32_t connector_type() const;
	uint32_t connector_type_id() const;
	uint32_t mmWidth() const;
	uint32_t mmHeight() const;
	uint32_t subpixel() const;
	const std::string& subpixel_str() const;
	std::vector<Videomode> get_modes() const;
	std::vector<Encoder*> get_encoders() const;
private:
	Connector(Card& card, uint32_t id, uint32_t idx);
	~Connector();

	void setup();
	void restore_mode();

	ConnectorPriv* m_priv;

	std::string m_fullname;

	Encoder* m_current_encoder;

	Crtc* m_saved_crtc;
};
}
