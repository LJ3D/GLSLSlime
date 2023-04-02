#include <glad/gl.h>

#include "debugging.hpp"

namespace openGLComponents{

    /*
        This isnt called just "texture" because it is not designed to be used for anything other than the simulation,
        and I dont want it to be confusing :)

        Basically this class is useless outside of exactly what im making it for.
    */
    class simulationTexture{
        private:
            unsigned int* textures;
            unsigned int res;

            // Le copypasta from the old version
            void makeTextures(unsigned int* textures, unsigned int n, unsigned int res){
                glGenTextures(n, textures);
                for (int i = 0; i < n; i++) {
                    GLCall(glActiveTexture(GL_TEXTURE0 + i));
                    GLCall(glBindTexture(GL_TEXTURE_2D, textures[i]));
                    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
                    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
                    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
                    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
                    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, res, res, 0, GL_RGBA, GL_FLOAT, NULL));
                }
            }
            void activebindtex(unsigned int tex, unsigned int texid, unsigned int unit){
                GLCall(glActiveTexture(GL_TEXTURE0 + texid));
                GLCall(glBindTextureUnit(unit, tex));
                GLCall(glBindImageTexture(unit, tex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F));
            }

        public:
            void init(unsigned int res){
                this->textures = new unsigned int[1];
                this->makeTextures(this->textures, 1, res);
                this->res = res;
            }

            void bind(){
                this->activebindtex(this->textures[0], 0, 0);
            }

            void update(float* data){
                GLCall(glActiveTexture(GL_TEXTURE0));
                GLCall(glBindTexture(GL_TEXTURE_2D, this->textures[0]));
                GLCall(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, this->res, this->res, GL_RGBA, GL_FLOAT, data));
            }

    };

}