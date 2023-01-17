#pragma once
#include <random>
#include <G3D/G3D.h>
#include "build_wave.h"


void build_wave() {
    G3D::TextOutput writer = G3D::TextOutput::TextOutput("scene/task4.Scene.Any");

    G3D::String string1 = R"(// -*- c++ -*-
{

	name = "Task 4";

	models = {
		cubeModel = ArticulatedModel::Specification {
			filename = "model/cube/cube.obj";
			preprocess = {
				setMaterial(all(), Color3(1,1,1));
				transformGeometry(all(), Matrix4::scale(1.0, 1.0, 1.0));
			};
		};
	};

	entities = {
		skybox = Skybox {
			texture = "cubemap/noonclouds/noonclouds_*.png";
	};)";

    G3D::String string2 = R"(camera = Camera {
			frame = CFrame::fromXYZYPRDegrees(-9,5,4,-90,-15,0);
		};  
	};
};)";

    writer.printf(string1);
    writer.writeNewline();

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(-1, 1);

    const int range = 10;
    double heights[101] = { 0 }; // One larger than the amount of cubes you have

    for (int i = 0; i < range; i++) {
        for (int j = 0; j < range; j++) {

            double variableHeight = distribution(generator);
            variableHeight += heights[i * 10 + j]; // Because this looks one back
            heights[i * 10 + j + 1] = variableHeight;

            writer.printf("cube");
            writer.writeNumber((i + j) * (i + j + 1) / 2 + i);
            writer.writeSymbol("= VisibleEntity {");
            writer.writeNewline();

            writer.printf("model = \"cubeModel\";");
            writer.writeNewline();

            writer.printf("frame = CFrame::fromXYZYPRDegrees(");
            writer.writeNumber(i);
            writer.printf(",");
            writer.writeNumber(variableHeight);
            writer.printf(",");
            writer.writeNumber(j);
            writer.printf(",0,0,0);");
            writer.writeNewline();

            writer.printf("};");
            writer.writeNewlines(2);
        
        }
    }

    writer.printf(string2);
    writer.commit();
}