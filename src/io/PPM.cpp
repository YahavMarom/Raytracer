
#include <fstream>
#include <iostream>
#include "PPM.h"

void writePPM(const Canvas& canvas, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) { 
        std::cout << "failed to create fail in PPM\n";
        return;
    }

    int width = canvas.getWidth();
    int height = canvas.getHeight();

    file << "P3" << "\n";
    file << width << " " << height << "\n";
    file << "255\n";


    for (int row = 0; row < height; row++ ){

        int lineLength = 0;

        for (int col = 0; col < width; col++ ) {
            
            Color color = canvas.pixelAt(col, row);

            int vals[3] = {
            std::clamp(static_cast<int>(255 * color.getRed()), 0, 255),
            std::clamp(static_cast<int>(255 * color.getGreen()), 0, 255),
            std::clamp(static_cast<int>(255 * color.getBlue()), 0, 255)
            };

            for (int val : vals) {
                std::string s = std::to_string(val);
                if (lineLength + static_cast<int>(s.length() ) + 1 > 70) {
                    file << "\n";
                    lineLength = 0;
                }
                file << s << " ";
                lineLength += static_cast<int>(s.length()) + 1;
            }
            
            
        }
        file << "\n";
    }

}
