
# fo (Frinx Object) File Format

Meshes Count (u8)
	Vertices Count (u16)
		{	Vertex Coordinate (float[3])
			TODO: UV Coordinate (float[2])	}
		* Vertices Count
	Faces Count (u16)
		Vertices ID (u16[3]) (Only triangular faces are allowed!)
		* Faces Count

*NOTE:* '\*' means multiplied by

