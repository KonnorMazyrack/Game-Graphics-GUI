#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
/* assimp include files. These three are usually needed. */
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

/* the global Assimp scene object */
const C_STRUCT aiScene* scene = NULL;
GLuint scene_list = 0;
C_STRUCT aiVector3D scene_min, scene_max, scene_center;

void initModel( const char* model_file )
{
	//const char* model_file = "basicCube.obj";
	//const char* model_file = "semi.obj";
		// Load the model file.
	if( 0 != loadasset( model_file ) ) {
		printf( "Failed to load model. Please ensure that the specified file exists." );
		//aiDetachAllLogStreams();
		return EXIT_FAILURE;
	}
}
void createSceneList()
{
	if( scene_list == 0 ) {
	    scene_list = glGenLists( 1 );
	    glNewList( scene_list, GL_COMPILE );
            /* now begin at the root node of the imported data and traverse
               the scenegraph by multiplying subsequent local transforms
               together on GL's matrix stack. */
	    recursive_render( scene, scene->mRootNode );
	    glEndList();
	}
}

void modelCleanUp()
{
	aiReleaseImport(scene);
	aiDetachAllLogStreams();
}
/* ---------------------------------------------------------------------------- */
void get_bounding_box_for_node (const C_STRUCT aiNode* nd,
	C_STRUCT aiVector3D* min,
	C_STRUCT aiVector3D* max,
	C_STRUCT aiMatrix4x4* trafo
){
	C_STRUCT aiMatrix4x4 prev;
	unsigned int n = 0, t;

	prev = *trafo;
	aiMultiplyMatrix4(trafo,&nd->mTransformation);

	for (; n < nd->mNumMeshes; ++n) {
		const C_STRUCT aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
		for (t = 0; t < mesh->mNumVertices; ++t) {

			C_STRUCT aiVector3D tmp = mesh->mVertices[t];
			aiTransformVecByMatrix4(&tmp,trafo);

			min->x = aisgl_min(min->x,tmp.x);
			min->y = aisgl_min(min->y,tmp.y);
			min->z = aisgl_min(min->z,tmp.z);

			max->x = aisgl_max(max->x,tmp.x);
			max->y = aisgl_max(max->y,tmp.y);
			max->z = aisgl_max(max->z,tmp.z);
		}
	}

	for (n = 0; n < nd->mNumChildren; ++n) {
		get_bounding_box_for_node(nd->mChildren[n],min,max,trafo);
	}
	*trafo = prev;
}

/* ---------------------------------------------------------------------------- */
void get_bounding_box(C_STRUCT aiVector3D* min, C_STRUCT aiVector3D* max)
{
	C_STRUCT aiMatrix4x4 trafo;
	aiIdentityMatrix4(&trafo);

	min->x = min->y = min->z =  1e10f;
	max->x = max->y = max->z = -1e10f;
	get_bounding_box_for_node(scene->mRootNode,min,max,&trafo);
}

/* ---------------------------------------------------------------------------- */
void color4_to_float4(const C_STRUCT aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

/* ---------------------------------------------------------------------------- */
void set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

/* ---------------------------------------------------------------------------- */
void apply_material(const C_STRUCT aiMaterial *mtl)
{
	float c[4];

	GLenum fill_mode;
	int ret1, ret2;
	C_STRUCT aiColor4D diffuse;
	C_STRUCT aiColor4D specular;
	C_STRUCT aiColor4D ambient;
	C_STRUCT aiColor4D emission;
	ai_real shininess, strength;
	int two_sided;
	int wireframe;
	unsigned int max;

	set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		color4_to_float4(&diffuse, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
		color4_to_float4(&specular, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

	set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
		color4_to_float4(&ambient, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
		color4_to_float4(&emission, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

	max = 1;
	ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
	if(ret1 == AI_SUCCESS) {
    	max = 1;
    	ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
		if(ret2 == AI_SUCCESS)
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
        else
        	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    }
	else {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	}

	max = 1;
	if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
		fill_mode = wireframe ? GL_LINE : GL_FILL;
	else
		fill_mode = GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

	max = 1;
	if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);
}

/* ---------------------------------------------------------------------------- */
void recursive_render( const C_STRUCT aiScene *sc, const C_STRUCT aiNode* nd )
{
	unsigned int i;
	unsigned int n = 0, t;
	C_STRUCT aiMatrix4x4 m = nd->mTransformation;

	/* update transform */
	aiTransposeMatrix4(&m);
	glPushMatrix();
	glMultMatrixf( (float*)&m );
	/* draw all meshes assigned to this node */
	for ( ; n < nd->mNumMeshes; ++n ) {
		const C_STRUCT aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

		apply_material( sc->mMaterials[mesh->mMaterialIndex] );

		if( mesh->mNormals == NULL ) {
			glDisable( GL_LIGHTING );
		} else {
			glEnable( GL_LIGHTING );
		}

		for( t = 0; t < mesh->mNumFaces; ++t ) {
			const C_STRUCT aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch( face->mNumIndices ) {
				case 1:  face_mode = GL_POINTS; break;
				case 2:  face_mode = GL_LINES; break;
				case 3:  face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}

			glBegin( face_mode );

			for( i = 0; i < face->mNumIndices; i++ ) {
				int index = face->mIndices[i];
				if( mesh->mColors[0] != NULL )
					glColor4fv( (GLfloat*)&mesh->mColors[0][index] );
				if( mesh->mNormals != NULL )
					glNormal3fv( &mesh->mNormals[index].x );
				glVertex3fv( &mesh->mVertices[index].x );
			}
			glEnd();
		}
	}

	/* draw all children */
	for( n = 0; n < nd->mNumChildren; ++n ) {
		recursive_render( sc, nd->mChildren[n] );
	}

	glPopMatrix();
}

int loadasset (const char* path)
{
	/* we are taking one of the postprocessing presets to avoid
	   spelling out 20+ single postprocessing flags here. */
	scene = aiImportFile( path,aiProcessPreset_TargetRealtime_MaxQuality );

	if( scene ) {
		get_bounding_box( &scene_min,&scene_max );
		scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
		scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
		scene_center.z = (scene_min.z + scene_max.z) / 2.0f;
		return 0;
	}
	return 1;
}
