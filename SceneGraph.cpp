#include "SceneGraph.h"
#include "Mesh.h"
#include "SceneManager.h"

Tmpl8::Node::Node()
{
	m_Mesh = NULL;
	m_Transform.Identity();
	m_Child.clear();
	m_Parent = NULL;
}

Tmpl8::Node::Node( Mesh* a_Mesh )
{
	m_Mesh = a_Mesh;
	m_Transform.Identity();
	m_Child.clear();
	m_Parent = NULL;
}

Tmpl8::Node::~Node()
{
	m_Mesh = NULL;
	m_Child.clear();
	m_Parent = NULL;
}

void Tmpl8::Node::Render( Tmpl8::matrix& a_Matrix )
{
	Tmpl8::matrix t = a_Matrix;
	t.Concatenate(m_Transform);

	if(m_Mesh != NULL)
	{
		Tmpl8::matrix t2 = SceneManager::Get()->GetScene()->GetActiveCamera()->GetMatrix();
		t2.Invert();
		t2.Concatenate(t);
		m_Mesh->Transform(t2);
		m_Mesh->Render();
	}

	for(unsigned int i = 0; i < m_Child.size(); ++i)
		m_Child[i]->Render(t);

	float A = cos( ToRad( m_Tilt ) );
	float B = sin( ToRad( m_Tilt ) );
	float C = cos( ToRad( m_Pan ) );
	float D = sin( ToRad( m_Pan ) );
	float E = cos( ToRad( m_Roll ) );
	float F = sin( ToRad( m_Roll ) );

	float AD = A * D;
	float BD = B * D;

	m_Transform.cell[ 0] =  C * E;
	m_Transform.cell[ 1] = -C * F;
	m_Transform.cell[ 2] = -D;
	m_Transform.cell[ 3] = m_Pos.x;

	m_Transform.cell[ 4] = -BD * E + A * F;
	m_Transform.cell[ 5] =  BD * F + A * E;
	m_Transform.cell[ 6] = -B * C;
	m_Transform.cell[ 7] = m_Pos.y;

	m_Transform.cell[ 8] =  AD * E + B * F;
	m_Transform.cell[ 9] = -AD * F + B * E;
	m_Transform.cell[10] =  A * C;
	m_Transform.cell[11] = m_Pos.z;

	m_Transform.cell[12] = 0;
	m_Transform.cell[13] = 0;
	m_Transform.cell[14] = 0;
	m_Transform.cell[15] = 1;

	m_Up = vector3( m_Transform.cell[1], m_Transform.cell[5], m_Transform.cell[9] );
	m_Side = vector3( m_Transform.cell[0], m_Transform.cell[4], m_Transform.cell[8] );
	m_Forward = vector3( m_Transform.cell[2], m_Transform.cell[6], m_Transform.cell[10] );
}

void Tmpl8::Node::AddChild( Node* a_Child )
{
	m_Child.push_back(a_Child);
	a_Child->m_Parent = this;
}

Tmpl8::Node* Tmpl8::Node::AddChild( std::string a_FileName, std::string a_Name )
{
	Node* node = new Node( SceneManager::Get()->GetScene()->GetMeshManager()->LoadMesh( a_FileName, a_Name ) );
	m_Child.push_back(node);
	node->m_Parent = this;

	return node;
}

void Tmpl8::Node::RemoveChild( Node* a_Child )
{
	for( std::vector<Node*>::iterator it = m_Child.begin(); it != m_Child.end(); it++ )
	{
		if( (*it) == a_Child )
		{
			m_Child.erase( it );
			return;
		}
	}
}

void Tmpl8::Node::Scale( float a_Scale )
{
	m_Mesh->Scale(a_Scale);
}