root.Fonts = {
    "Default": {
        Type: FontType.Basic,
        Sheet: "Font",
        Columns: 64,
        Rows: 43,
        Widths: new Array(64 * 43),
        DesignColWidth: 32,
        LineSpacing: 22,
    }
};

var westernWidths = [
    0x20, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1A, 0x08, 0x18, 0x18,
	0x1A, 0x18, 0x1A, 0x18, 0x1A, 0x19, 0x1C, 0x19, 0x18, 0x1A, 0x16, 0x16,
	0x18, 0x18, 0x08, 0x12, 0x17, 0x16, 0x1E, 0x18, 0x1A, 0x16, 0x1A, 0x18,
	0x18, 0x1A, 0x18, 0x1C, 0x1E, 0x1A, 0x1A, 0x18, 0x14, 0x14, 0x14, 0x14,
	0x14, 0x12, 0x14, 0x12, 0x08, 0x0E, 0x14, 0x08, 0x1C, 0x14, 0x16, 0x14,
	0x14, 0x0F, 0x14, 0x12, 0x14, 0x16, 0x1C, 0x16, 0x12, 0x14, 0x11, 0x11,
	0x08, 0x08, 0x08, 0x09, 0x10, 0x08, 0x0B, 0x09, 0x08, 0x08, 0x0E, 0x0E,
	0x0A, 0x0A, 0x0C, 0x0C, 0x0B, 0x0B, 0x0A, 0x0A, 0x0D, 0x0D, 0x10, 0x10,
	0x0D, 0x0D, 0x0E, 0x0E, 0x0D, 0x0D, 0x18, 0x18, 0x0D, 0x0D, 0x0A, 0x20,
	0x1C, 0x1A, 0x16, 0x1E, 0x18, 0x17, 0x16, 0x18, 0x1A, 0x18, 0x18, 0x18,
	0x18, 0x18, 0x18, 0x18, 0x16, 0x18, 0x18, 0x18, 0x18, 0x18, 0x14, 0x16,
	0x16, 0x18, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
];

for (var i = 0; i < 64 * 43; i++) {
    if (i < westernWidths.length) {
        root.Fonts["Default"].Widths[i] = westernWidths[i];
    } else {
        root.Fonts["Default"].Widths[i] = root.Fonts["Default"].DesignColWidth;
    }
}