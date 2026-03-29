/*
Shader Type	Stage in Pipeline	Purpose
Vertex Shader (vert)	Vertex Processing	Transform vertices, pass attributes.
Fragment Shader (frag)	Fragment Processing	Compute per-pixel color.
Geometry Shader (geom)	Primitive Processing	Generate or modify primitives.
Tessellation Control (tess_control)	Tessellation Setup	Define tessellation factors.
Tessellation Evaluation (tess_eval)	Tessellated Vertex Stage	Calculate positions of tessellated geometry.
Compute Shader (comp)	Independent Compute	General-purpose parallel computation.
Task Shader (task)	Mesh Shading (Vulkan)	Organize work for mesh shaders.
Mesh Shader (mesh)	Mesh Generation (Vulkan)	Replace vertex/geometry shaders.
Ray Generation (rgen)	Ray Tracing	Initiate ray tracing.
Intersection (rint)	Ray Tracing	Handle ray intersections with custom objects.
Any-Hit (rahit)	Ray Tracing	Process every hit along a ray’s path.
Closest-Hit (rchit)	Ray Tracing	Process the closest ray intersection.
Miss Shader (rmiss)	Ray Tracing	Handle rays that miss geometry.
*/

/*

Shader Type	Common File Extensions	Description
Vertex Shader	.vert, .vs, .vsh	For vertex shaders.
Fragment Shader	.frag, .fs, .fsh	For fragment (pixel) shaders.
Geometry Shader	.geom, .gs	For geometry shaders.
Tessellation Control Shader	.tesc, .tc	For tessellation control shaders.
Tessellation Evaluation Shader	.tese, .te	For tessellation evaluation shaders.
Compute Shader	.comp, .cs	For compute shaders.
Task Shader (Vulkan)	.task, .ts	For task shaders in mesh shading pipelines.
Mesh Shader (Vulkan)	.mesh, .ms	For mesh shaders in mesh shading pipelines.
Ray Generation Shader	.rgen	For ray generation shaders in ray tracing.
Intersection Shader	.rint	For intersection shaders in ray tracing.
Any-Hit Shader	.rahit	For any-hit shaders in ray tracing.
Closest-Hit Shader	.rchit	For closest-hit shaders in ray tracing.
Miss Shader	.rmiss	For miss shaders in ray tracing.
Callable Shader	.rcall	For callable shaders in ray tracing.
*/
/*

Vertex Shader	        vert	Compiles as a vertex shader.
Fragment Shader	        frag	Compiles as a fragment shader.
Geometry Shader	        geom	Compiles as a geometry shader.
Tessellation Control	tesc	Compiles as a tessellation control shader.
Tessellation Evaluation	tese	Compiles as a tessellation evaluation shader.
Compute Shader	        comp	Compiles as a compute shader.
Task Shader	            task	Compiles as a task shader (Vulkan mesh shading).
Mesh Shader	            mesh	Compiles as a mesh shader (Vulkan mesh shading).
Ray Generation	        rgen	Compiles as a ray generation shader.
Intersection	        rint	Compiles as a ray intersection shader.
Any-Hit	                rahit	Compiles as a ray any-hit shader.
Closest-Hit	            rchit	Compiles as a ray closest-hit shader.
Miss	                rmiss	Compiles as a ray miss shader.
Callable	            rcall	Compiles as a ray callable shader.
*/

#define _EXT(s) "."+s
#define vert  "vert"     
#define frag  "frag"     
#define geom  "geom"     
#define tesc  "tesc"     
#define tese  "tese"     
#define comp  "comp"     
#define task  "task"     
#define mesh  "mesh"     
#define rgen  "rgen"     
#define rint  "rint"     
#define rahit "rahit"    
#define rchit "rchit"    
#define rmiss "rmiss"    
#define rcall "rcall"    
