
# fo (Frinx Object) File Format

Meshes Count (u8)
	Vertices Count (u16)
		{	Vertex Coordinate (float[3])
			UV Coordinate (float[2])#	}
		* Vertices Count
	Faces Count (u16)
		Vertices ID (u16[3]) (Only triangular faces are allowed!)
		* Faces Count

*NOTE:* '\*' means multiplied by
\#: The textures are up-down flipped, so the uv's y axis should be
flipped (1.0-y) when loading.
