#include "SpriteSurface.h"
#include "../Graphics/TextureHandler.h"

SpriteSurface::SpriteSurface(std::string name_, float scale_, float angle_, glm::vec4 tint_): VAO(0),VBO(0),angle(0),name(std::string()),scale(glm::vec2(1.0,1.0))
{
    name = name_;
   
    scale = glm::vec2(scale_, scale_);
    angle = angle_;

    spriteSufaceVertex[0].position = glm::vec2(-0.5, 0.5);
    spriteSufaceVertex[0].textureCoordinates = glm::vec2(0.0, 0.0f);

    spriteSufaceVertex[1].position = glm::vec2(0.5, 0.5);
    spriteSufaceVertex[1].textureCoordinates = glm::vec2(1.0, 0.0);

    spriteSufaceVertex[2].position = glm::vec2(-0.5, -0.5);
    spriteSufaceVertex[2].textureCoordinates = glm::vec2(0.0, 1.0);

    spriteSufaceVertex[3].position = glm::vec2(0.5, -0.5);
    spriteSufaceVertex[3].textureCoordinates = glm::vec2(1.0, 1.0);
    
    if (TextureHandler::GetInstance()->GetTexture(name)==0)
    {
        TextureHandler::GetInstance()->CreateTexture(name, "C:/Users/jalbm/Desktop/3D_Engine-master/GameEngine/GameEngine/Resources/Textures/kisspng-insurance-sustainability-united-nations-environmen-crosshair-5a732ba079b494.0158206215174972484985.png");
        width=TextureHandler::GetInstance()->GetTextureData(name)->width;
        height = TextureHandler::GetInstance()->GetTextureData(name)->height;
        textureID = TextureHandler::GetInstance()->GetTexture(name);
    }
    else
    {
        std::cout << "Sprite Surface, couldn't create a new texture";
        return; 
    }
    GenerateBuffers();
}

SpriteSurface::~SpriteSurface()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &VBO);

}

void SpriteSurface::Draw(Camera* camera_, std::vector<glm::vec2> position_)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetOrthographic()));
    glUniformMatrix4fv(tintColour, 1, GL_FALSE,NULL);

    glUniform3f(projLoc,
        camera_->GetPosition().x,
        camera_->GetPosition().y, 
        camera_->GetPosition().z);

    glBindVertexArray(VAO);
    for (int i = 0; i < position_.size(); i++)
    {
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(position_[i]));
        glDrawArrays(GL_TRIANGLE_STRIP, 0, spriteSufaceVertex.size());
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

int SpriteSurface::getWidth()
{
    return width;
}

int SpriteSurface::getHeight()
{
    return height;
}

glm::vec2 SpriteSurface::minVert()
{
    return spriteSufaceVertex[0].position;
}

void SpriteSurface::GenerateBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBufferData(GL_ARRAY_BUFFER, spriteSufaceVertex.size() * sizeof(Vertex), &spriteSufaceVertex[0], GL_STATIC_DRAW);

    //POSTION
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

    // TEXTURECOORDINATES
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

 //   modelLoc = glGetUniformLocation(modelLoc, "model");
//    projectionLoc = glGetUniformLocation(projectionLoc, "proj");
 //   textureLoc= glGetUniformLocation()

}
