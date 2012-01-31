
# fo (Frinx Object) File Format

Meshes Count (u8)
	Vertices Count (u16)
		Vertex Coordinate (float[3])
		* Vertices Count
	Faces Count (u16)
		{	Vertices ID (u16[3]) (Only triangular faces are allowed!)
			UV Coordinate (float[3][2])#	}
		* Faces Count

*NOTES:*
* '\*' means multiplied by
* UV must be per-faced.
* #: The textures are upside-down flipped, so the uv's y axis should be
flipped (1.0-y) when loading.
* For the Face isn't 4-byte-aligned, no using of READ\_ARRAY!

