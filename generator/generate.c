#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <json-c/json.h>

#include "modes.h"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int generate_modes_json(const struct drm_display_mode *modes,
			unsigned int count,
			char *prefix, char *filename)
{
	struct json_object *json_file = json_object_new_object();
	int i;

	for (i = 0 ; i < count ; ++i) {
		struct json_object *mode, *val;
		char id[255];

		snprintf(id, 255, "%s-%d", prefix, i);

		if (strlen(modes[i].name) <= 0)
			continue;

		mode = json_object_new_object();

		json_object_object_add(mode, "name",
				       json_object_new_string(modes[i].name));
		json_object_object_add(mode, "clock",
				       json_object_new_int(modes[i].clock));
		json_object_object_add(mode, "hdisplay",
				       json_object_new_int(modes[i].hdisplay));
		json_object_object_add(mode, "hsync_start",
				       json_object_new_int(modes[i].hsync_start));
		json_object_object_add(mode, "hsync_end",
				       json_object_new_int(modes[i].hsync_end));
		json_object_object_add(mode, "htotal",
				       json_object_new_int(modes[i].htotal));
		json_object_object_add(mode, "hskew",
				       json_object_new_int(modes[i].hskew));
		json_object_object_add(mode, "vdisplay",
				       json_object_new_int(modes[i].vdisplay));
		json_object_object_add(mode, "vsync_start",
				       json_object_new_int(modes[i].vsync_start));
		json_object_object_add(mode, "vsync_end",
				       json_object_new_int(modes[i].vsync_end));
		json_object_object_add(mode, "vtotal",
				       json_object_new_int(modes[i].vtotal));
		json_object_object_add(mode, "vscan",
				       json_object_new_int(modes[i].vscan));
		if (modes[i].flags & DRM_MODE_FLAG_PHSYNC)
			json_object_object_add(mode, "phsync",
					       json_object_new_boolean(1));
		if (modes[i].flags & DRM_MODE_FLAG_NHSYNC)
			json_object_object_add(mode, "nhsync",
					       json_object_new_boolean(1));
		if (modes[i].flags & DRM_MODE_FLAG_PVSYNC)
			json_object_object_add(mode, "pvsync",
					       json_object_new_boolean(1));
		if (modes[i].flags & DRM_MODE_FLAG_NVSYNC)
			json_object_object_add(mode, "nvsync",
					       json_object_new_boolean(1));
		if (modes[i].flags & DRM_MODE_FLAG_INTERLACE)
			json_object_object_add(mode, "interlace",
					       json_object_new_boolean(1));
		if (modes[i].flags & DRM_MODE_FLAG_DBLSCAN)
			json_object_object_add(mode, "double-scan",
					       json_object_new_boolean(1));
		if (modes[i].flags & DRM_MODE_FLAG_DBLCLK)
			json_object_object_add(mode, "double-clock",
					       json_object_new_boolean(1));
		if (modes[i].flags & DRM_MODE_FLAG_CLKDIV2)
			json_object_object_add(mode, "clockdiv2",
					       json_object_new_boolean(1));
		json_object_object_add(mode, "vrefresh",
				       json_object_new_int(modes[i].vrefresh));

		json_object_object_add(json_file, id, mode);
	}

	json_object_to_file(filename, json_file);

	json_object_put(json_file);

	return 0;
}

int main()
{
	int ret;

	ret = generate_modes_json(drm_dmt_modes, ARRAY_SIZE(drm_dmt_modes),
				  "DMT", "dmt_modes.json");
	if (ret)
		return 1;

	ret = generate_modes_json(edid_est_modes, ARRAY_SIZE(edid_est_modes),
				  "EST", "est_modes.json");
	if (ret)
		return 1;

	ret = generate_modes_json(edid_cea_modes, ARRAY_SIZE(edid_cea_modes),
				  "CEA-VIC", "cea_modes.json");
	if (ret)
		return 1;

	ret = generate_modes_json(edid_4k_modes,  ARRAY_SIZE(edid_4k_modes),
				  "HDMI-VIC:", "hdmi_4k_modes.json");
	if (ret)
		return 1;

	return 0;
}
