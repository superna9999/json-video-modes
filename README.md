Video Display Timings in JSON format
====================================

This is useful to be able to parse and detect a timing in something not in C,
and use very complete data like the Linux DRM EDID modes list.

The JSON Format is pretty simple, and is a simple mapping of the linux "struct drm_display_mode"

```
{
   "CEA-VIC-16" : {
      "vsync_end" : 1089,
      "vdisplay" : 1080,
      "hdisplay" : 1920,
      "pvsync" : true,
      "vscan" : 0,
      "hskew" : 0,
      "hsync_end" : 2052,
      "name" : "1920x1080",
      "vsync_start" : 1084,
      "clock" : 148500,
      "phsync" : true,
      "hsync_start" : 2008,
      "htotal" : 2200,
      "vrefresh" : 60,
      "vtotal" : 1125
   },
   ...
}	
```

Properties are :
  * name: Mode name
  * clock: Pixel clock in kHz
  * hdisplay: horizontal display size
  * hsync_start: horizontal sync start
  * hsync_end: horizontal sync end
  * htotal: horizontal total size
  * hskew: horizontal skew
  * vdisplay: vertical display size
  * vsync_start: vertical sync start
  * vsync_end: vertical sync end
  * vtotal: vertical total size
  * vscan:  vertical scan
  * phsync: true if horizontal sync is active high
  * nhsync: true if horizontal sync is active low
  * pvsync: true if vertical sync is active high
  * nvsync: true if vertical sync is active low
  * interlace: true if mode is interlaced
  * double-scan: true if mode uses doublescan
  * double-clock: true if double-clocked mode
  * clockdiv2: true if half-clocked mode
  * vrefresh: Vertical refresh rate in Hz

Files are divided in 4:
  * dmt_modes.json : Autogenerated from the DMT spec
  * est_modes.json : These more or less come from the DMT spec.  The 720x400 modes are inferred from historical 80x25 practice.  The 640x480@67 and 832x624@75 modes are old-school Mac modes.  The EDID spec says the 1152x864@75 mode should be 1152x870, again for the Mac, but instead we use the x864 DMT mode
  * cea_modes.json : Probably taken from CEA-861 spec
  * hdmi_4k_modes.json : HDMI 1.4 4k modes