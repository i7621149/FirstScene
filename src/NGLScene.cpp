#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <iostream>
#include <ngl/NGLStream.h>

#include <cstdlib>

NGLScene::NGLScene()
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  setTitle("Shader Tests");

  m_view = ngl::lookAt(ngl::Vec3(2,2,2), ngl::Vec3(0,0,0), ngl::Vec3(0,1,0));

  m_time = 0;

  m_mode = 0;
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL(QResizeEvent *_event)
{
  m_width=_event->size().width()*devicePixelRatio();
  m_height=_event->size().height()*devicePixelRatio();

  m_project = ngl::perspective(45.0f,
                               float(m_width/m_height),
                               0.2f,
                               20.0f
                               );
}

void NGLScene::resizeGL(int _w , int _h)
{
  m_width=_w*devicePixelRatio();
  m_height=_h*devicePixelRatio();

  m_project = ngl::perspective(45.0f,
                               float(m_width/m_height),
                               0.2f,
                               20.0f
                               );
}


void NGLScene::initializeGL()
{
  // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
  // be done once we have a valid GL context but before we call any GL commands. If we dont do
  // this everything will crash
  ngl::NGLInit::instance();
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);
  //createQuad();

  //create sphere on initialize
  ngl::VAOPrimitives::instance()->createSphere("mySphere", 1.0, 100);

  //instance of shader manager
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  shader->createShaderProgram("diffuse");

  //attatch two shader stages to the shader
  shader->attachShader("diffuseVertex", ngl::ShaderType::VERTEX);
  shader->attachShader("diffuseFragment", ngl::ShaderType::FRAGMENT);

  //load the shaders text source
  shader->loadShaderSource("diffuseVertex", "shaders/DiffuseVertex.glsl");
  shader->loadShaderSource("diffuseFragment", "shaders/DiffuseFragment.glsl");

  //compile source code
  shader->compileShader("diffuseVertex");
  shader->compileShader("diffuseFragment");

  //attach to created program
  shader->attachShaderToProgram("diffuse", "diffuseVertex");
  shader->attachShaderToProgram("diffuse", "diffuseFragment");

  //link it up
  shader->linkProgramObject("diffuse");
  //tell shader to use it
  shader->use("diffuse");

  shader->setRegisteredUniform("color", 1.0f, 0.0f, 0.0f, 1.0f);
  shader->setRegisteredUniform("lightPos", 0.0f, 2.0f, 0.0f);
  shader->setRegisteredUniform("lightDiffuse", 1.0f, 1.0f, 1.0f, 1.0f);
  shader->setRegisteredUniform("ambientLightDirection", 0.5f, 1.0f, 0.5f);

  startTimer(40);

}



void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glViewport(0,0,m_width,m_height);
  ngl::VAOPrimitives *prim = ngl::VAOPrimitives::instance();
  /*
  m_currentMatID = 0;
  m_transform.reset();
  m_transform.setScale(1.0, 1.0, 1.0);
  loadMatricesToShader();
  prim->draw("mySphere");

  m_currentMatID = 1;
  m_transform.reset();
  m_transform.setScale(0.3, 0.3, 0.3);
  m_transform.setPosition(0.5, 1.0, 0.0);
  loadMatricesToShader();
  prim->draw("mySphere");

  m_currentMatID = 1;
  m_transform.reset();
  m_transform.setScale(0.3, 0.3, 0.3);
  m_transform.setPosition(-0.5, 1.0, 0.0);
  loadMatricesToShader();
  prim->draw("mySphere");

  m_currentMatID = 2;
  m_transform.reset();
  m_transform.setScale(0.1, 0.1, 0.1);
  m_transform.setPosition(0.5, 1.3, 0.0);
  loadMatricesToShader();
  prim->draw("mySphere");

  m_currentMatID = 2;
  m_transform.reset();
  m_transform.setScale(0.1, 0.1, 0.1);
  m_transform.setPosition(-0.5, 1.3, 0.0);
  loadMatricesToShader();
  prim->draw("mySphere");

  m_currentMatID = 2;
  m_transform.reset();
  m_transform.setScale(0.4, 0.1, 0.4);
  m_transform.setPosition(0.5, 0.6, 0.8);
  loadMatricesToShader();
  prim->draw("mySphere");
  */

  m_currentMatID = 0;
  m_transform.reset();
  m_transform.setScale(1.5f, 1.5f, 1.5f);
  loadMatricesToShader();
  prim->draw("teapot");


  //can be printed with ngl/NGLStream.h
  std::cout << m_view << std::endl;
  std::cout << m_project << std::endl << std::endl;
}

void NGLScene::loadMatricesToShader()
{
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  ngl::Mat4 MVP = m_transform.getMatrix() * m_view * m_project;

  shader->setRegisteredUniform("MVP", MVP);
  shader->setRegisteredUniform("matID", m_currentMatID);
}

void NGLScene::createQuad()
{
  // a simple quad object
  float* vert = new float[18];	// vertex array
  const static float s=0.8;
  vert[0] =-s; vert[1] =  s; vert[2] =-1.0;
  vert[3] = s; vert[4] =  s; vert[5] =-1.0;
  vert[6] = -s; vert[7] = -s; vert[8]= -1.0;

  vert[9] =-s; vert[10]= -s; vert[11]=-1.0;
  vert[12] =s; vert[13]= -s; vert[14]=-1.0;
  vert[15] =s; vert[16]= s; vert[17]=-1.0;
  // allocate a VertexArray
  glGenVertexArrays(1, &m_vaoID);
  // now bind a vertex array object for our verts
  glBindVertexArray(m_vaoID);
  // now we are going to bind this to our vbo
  GLuint vboID;
  glGenBuffers(1, &vboID);
  // now bind this to the VBO buffer
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  // allocate the buffer datra
  glBufferData(GL_ARRAY_BUFFER, 18*sizeof(GLfloat), vert, GL_STATIC_DRAW);
  // now fix this to the attribute buffer 0
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  // enable and bind this attribute (will be inPosition in the shader)
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);

  delete [] vert;
}


//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseMoveEvent (QMouseEvent * _event)
{

}


//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mousePressEvent ( QMouseEvent * _event)
{

}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseReleaseEvent ( QMouseEvent * _event )
{

}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::wheelEvent(QWheelEvent *_event)
{

}
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow

  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  int newMode = m_mode;
  switch (_event->key())
  {
  // escape key to quite
    case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
    case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
    case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
    case Qt::Key_0 : newMode = 0; break;
    case Qt::Key_1 : newMode = 1; break;
    case Qt::Key_2 : newMode = 2; break;
    case Qt::Key_3 : newMode = 3; break;
    case Qt::Key_4 : newMode = 4; break;
    default : break;
  }
  // finally update the GLWindow and re-draw
  if(newMode != m_mode){
    m_mode = newMode;
    shader->setRegisteredUniform("mode", m_mode);
  }
  update();
}

void NGLScene::timerEvent(QTimerEvent *)
{
  m_time++;
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  shader->setRegisteredUniform("time", m_time);
  update();
}

