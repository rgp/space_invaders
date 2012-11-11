#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include  "enemies.h"

#include <assert.h>
#include <fstream>

#include "imageloader.h"

using namespace std;

void Enemies::loadTexture(Image* image,int k)
{

  glBindTexture(GL_TEXTURE_2D, this->texName[k]); //Tell OpenGL which texture to edit

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);

  //Map the image to the texture
  glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
      0,                            //0 for now
      GL_RGB,                       //Format OpenGL uses for image
      image->width, image->height,  //Width and height
      0,                            //The border of the image
      GL_RGB, //GL_RGB, because pixels are stored in RGB format
      GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
      //as unsigned numbers
      image->pixels);               //The actual pixel data

}

void Enemies::generate(){
  for(int i = 0;i<4;i++){
    for(int j = 0;j<8;j++){
      this->alive[i][j] = i+1;
    }
  }
  this->direction = 0.7;

  this->padding = 10;

  this->full_width = 8*this->width + 7*this->padding;
  this->full_height = 4*this->height + 3*this->padding;

  glGenTextures(6, this->texName); //Make room for our texture
  Image* image = loadBMP("images/aliens1.bmp");
  this->loadTexture(image,0);
  image = loadBMP("images/aliens2.bmp");
  loadTexture(image,1);
  image = loadBMP("images/aliens3.bmp");
  loadTexture(image,2);
  image = loadBMP("images/aliens4.bmp");
  loadTexture(image,3);
  image = loadBMP("images/aliens5.bmp");
  loadTexture(image,4);
  image = loadBMP("images/aliens6.bmp");
  loadTexture(image,5);

  delete image;
  
}

void Enemies::draw_one(int a){
  //glColor4f(1.0,0.0,0.0,1.0);
  //glLineWidth(1);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texName[a]);

  glBegin(GL_QUADS); 
    glTexCoord2f(0.0f, 0.0f);
  glVertex2f(0,0);
    glTexCoord2f(0.0f, 1.0f);
  glVertex2f(0,this->height);
    glTexCoord2f(1.0f, 1.0f);
  glVertex2f(this->width, this->height);
    glTexCoord2f(1.0f, 0.0f);
  glVertex2f(this->width,0);
  glEnd();
}

void Enemies::draw(){
  glPushMatrix();
  glTranslatef(x,y,0);
  for(int i = 0;i<4;i++){
    glPushMatrix();
    glTranslatef(0,-i*(this->height+this->padding),0);
    for(int j = 0;j<8;j++){
      glPushMatrix();
      glTranslatef(j*(this->width+this->padding),0,0);
      if(this->alive[i][j] > 0)
        draw_one(this->alive[i][j]);
      glPopMatrix();
    }
    glPopMatrix();
  }
  glPopMatrix();
}

void Enemies::update(){

  if(
      this->x <= (95 - this->full_width) &&
      this->x >= -95 
    ){
    this->translateX(this->direction);
  }else{
    this->direction = -1 * this->direction;
    this->translateX(this->direction);
    this->translateY(-1);
  }
}

int Enemies::getIndexX(double fX){
  int ind = (fX - this->x)/(this->width+this->padding);
  int a = ind*(this->width+this->padding)+this->x;
  if(fX > a && fX < + this->width){
    return ind;
  }else{
    return -1;
  }
}

int Enemies::getIndexY(double fY){
  return (this->y-fY)/(this->width+this->padding);
}

bool Enemies::collided(double fX, double fY){
  if (
      (this->x + this->full_width >= fX) && (this->x <= fX)
      && 
      ((this->y - this->full_height <= fY) && (this->y >= fY))
     )
  {
    int _x = (fX - this->x)/(this->width+this->padding);
    if(fX >= _x * (this->width+this->padding)+ this->x &&
        fX <= _x * (this->width+this->padding)+ this->x + this->width
      ){
      int _y = (fY - (this->y - this->full_height))/(this->height+this->padding);
        _y = 3 - _y;
      if(
          fY >= (this->y - _y*(this->height+this->padding))
        ){
        if(this->alive[_y][_x] > 0){
          this->alive[_y][_x] = 0;
          return true;
        }
      }
    }
  }
  return false;
}


#include <assert.h>
#include <fstream>

#include "imageloader.h"

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h)
{

}

Image::~Image()
{
    delete[] pixels;
}

namespace
{
//Converts a four-character array to an integer, using little-endian form
    int toInt(const char* bytes)
    {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }

//Converts a two-character array to a short, using little-endian form
    short toShort(const char* bytes)
    {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }

//Reads the next four bytes as an integer, using little-endian form
    int readInt(ifstream &input)
    {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }

//Reads the next two bytes as a short, using little-endian form
    short readShort(ifstream &input)
    {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }

//Just like auto_ptr, but for arrays
    template<class T>
    class auto_array
    {
    private:
        T* array;
        mutable bool isReleased;
    public:
        explicit auto_array(T* array_ = NULL) :
                array(array_), isReleased(false)
        {
        }

        auto_array(const auto_array<T> &aarray)
        {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        ~auto_array()
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
        }

        T* get() const
        {
            return array;
        }

        T &operator*() const
        {
            return *array;
        }

        void operator=(const auto_array<T> &aarray)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }

        T* operator->() const
        {
            return array;
        }

        T* release()
        {
            isReleased = true;
            return array;
        }

        void reset(T* array_ = NULL)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = array_;
        }

        T* operator+(int i)
        {
            return array + i;
        }

        T &operator[](int i)
        {
            return array[i];
        }
    };
}

Image* loadBMP(const char* filename)
{
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);

    //Read the header
    int headerSize = readInt(input);
    int width;
    int height;
    switch (headerSize)
    {
    case 40:
        //V3
        width = readInt(input);
        height = readInt(input);
        input.ignore(2);
        assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
        assert(readShort(input) == 0 || !"Image is compressed");
        break;
    case 12:
        //OS/2 V1
        width = readShort(input);
        height = readShort(input);
        input.ignore(2);
        assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
        break;
    case 64:
        //OS/2 V2
        assert(!"Can't load OS/2 V2 bitmaps");
        break;
    case 108:
        //Windows V4
        assert(!"Can't load Windows V4 bitmaps");
        break;
    case 124:
        //Windows V5
        assert(!"Can't load Windows V5 bitmaps");
        break;
    default:
        assert(!"Unknown bitmap format");
    }

    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);

    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                pixels2[3 * (width * y + x) + c] =
                    pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }

    input.close();
    return new Image(pixels2.release(), width, height);
}


