#pragma once
#include <G3D/G3D.h>
#include "build_spiral.h"

void build_file() {
    G3D::TextOutput writer = G3D::TextOutput::TextOutput("scene/task3.Scene.Any");

    G3D::String string1 = R"(// -*- c++ -*-
{

name = "Task 3";

models = {
	cubeModel = ArticulatedModel::Specification {
		filename = "model/cube/cube.obj";
		preprocess = {
			setMaterial(all(), "material/roughcedar/roughcedar-lambertian.png");
			transformGeometry(all(), Matrix4::scale(0.3, 0.1, 2.0));
		};
	};
};

entities = {
	skybox = Skybox {
		texture = "cubemap/whiteroom/whiteroom-*.png";
	};

	sun = Light {
		attenuation = (0,0,1);
		bulbPower = Power3(4e+006);
		frame = CFrame::fromXYZYPRDegrees(-15, 807, -41, -164, -77, 77);
		shadowMapSize = Vector2int16(2048, 2048);
		spotHalfAngleDegrees = 5;
		rectangular = true;
		type = "SPOT";
	};
)";

    G3D::String string2 = R"(
		camera = Camera {
			frame = CFrame::fromXYZYPRDegrees(0,0,5);
		};
	};
};)";

    writer.printf(string1);
    writer.writeNewline();

    for (int i = 0; i < 50; i++) {


        writer.printf("stair");
        writer.writeNumber(i);
        writer.writeSymbol("= VisibleEntity {");
        writer.writeNewline();

        writer.printf("model = \"cubeModel\";");
        writer.writeNewline();

        writer.printf("frame = CFrame::fromXYZYPRDegrees(");
        writer.writeNumber(0);
        writer.printf(",");
        writer.writeNumber(i * 0.1);
        writer.printf(",");
        writer.writeNumber(0);
        writer.printf(",");
        writer.writeNumber(i * 17.0);
        writer.printf(",0,0);");
        writer.writeNewline();

        writer.printf("};");
        writer.writeNewlines(2);
    }

    writer.printf(string2);
    writer.commit();
}