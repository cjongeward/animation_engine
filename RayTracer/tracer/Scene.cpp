#include "Scene.h"
#include "Shapes.h"
#include "Settings.h"
#include "MeshReader.h"

std::unique_ptr<Shape> Scene::getRootShape()
{
  // Assembles a room with a bunch of crap in it
  Sphere sphere{ vec{7.f, -3.f, -17.f}, MIRRORISH, 1.f };
  Sphere sphere2{ vec{9.5f, -0.35f, -15.f}, BRIGHT, 0.3f };
  Sphere sphere3{ vec{9.5f, -0.35f, -16.f}, BLACKISH, 0.3f };
  Sphere sphere4{ vec{9.5f, -0.35f, -17.f}, DULL, 0.3f };
  Sphere sphere5{ vec{9.5f, -0.35f, -18.f}, WHITEISH, 0.3f };
  Box box1{vec{0.f, 0.f, 0.f}, MIRRORISH};
  box1.transform(mat::translation(vec{9.5f, -0.35f, -6.f}) * mat::rotation(0.f, PI4, PI4) * mat::scale(vec{0.4f, 0.4f, 0.4f}));
  Box box2{vec{0.f, 0.f, 0.f}, WHITEISH};
  box2.transform(mat::translation(vec{9.5f, -0.35f, -5.f}) * mat::rotation(0.f, PI4, PI4) * mat::scale(vec{0.4f, 0.4f, 0.4f}));

  Box plank{vec{0.f, 0.f, 0.f}, BROWNISH};
  plank.transform(mat::translation(vec{9.5f, -0.7f, -17.f}) * mat::scale(vec{1.0f, 0.15f, 5.f}) );
  Box plank2{vec{0.f, 0.f, 0.f}, BROWNISH};
  plank2.transform(mat::translation(vec{9.5f, -0.7f, -4.f}) * mat::scale(vec{1.0f, 0.15f, 5.f}) );


  Box fixture1{vec{0.f, 0.f, 0.f}, BLACKISH};
  fixture1.transform(mat::translation(vec{0.f, -0.75f, 1.f}) * mat::scale(vec{0.1f, 1.5f, 0.1f}));
  Box fixture12{vec{0.f, 0.f, 0.f}, BLACKISH};
  fixture12.transform(mat::translation(vec{0.f, 0.f, 0.5f}) * mat::scale(vec{0.1f, 0.1f, 1.f}));
  Box fixture13{vec{0.f, 0.f, 0.f}, BLACKISH};
  fixture13.transform(mat::translation(vec{0.f, -0.75f, 0.5f}) * mat::scale(vec{0.1f, 0.1f, 1.f}));
  Sphere light_bulb{ vec{0.f, -1.5f, 1.f}, LIGHT, 0.1f };
  std::unique_ptr<CompositeShape> fixture = std::make_unique<CompositeShape>(vec{ 0.f, 0.f, 0.f }, 2.2f);
  fixture->shapes.push_back(std::make_unique<Box>(fixture1));
  fixture->shapes.push_back(std::make_unique<Box>(fixture12));
  fixture->shapes.push_back(std::make_unique<Box>(fixture13));
  fixture->shapes.push_back(std::make_unique<Sphere>(light_bulb));
  fixture->transform(mat::translation(vec{ -6.f, 4.5f, -20.f }));
  std::unique_ptr<CompositeShape> fixture2 = std::make_unique<CompositeShape>(vec{ 0.f, 0.f, 0.f }, 2.2f);
  fixture2->shapes.push_back(std::make_unique<Box>(fixture1));
  fixture2->shapes.push_back(std::make_unique<Box>(fixture12));
  fixture2->shapes.push_back(std::make_unique<Box>(fixture13));
  fixture2->shapes.push_back(std::make_unique<Sphere>(light_bulb));
  fixture2->transform(mat::translation(vec{ 6.f, 4.5f, -20.f }));
  std::unique_ptr<CompositeShape> fixture3 = std::make_unique<CompositeShape>(vec{ 0.f, 0.f, 0.f }, 2.2f);
  fixture3->shapes.push_back(std::make_unique<Box>(fixture1));
  fixture3->shapes.push_back(std::make_unique<Box>(fixture12));
  fixture3->shapes.push_back(std::make_unique<Box>(fixture13));
  fixture3->shapes.push_back(std::make_unique<Sphere>(light_bulb));
  fixture3->transform(mat::translation(vec{ 0.f, 4.5f, -20.f }));

  Sphere sun{ vec{200.f, 80.f, 60.f}, SUN, 0.25f };

  Box win1{vec{0.f, 0.f, 0.f}, BLACKISH};
  win1.transform(mat::translation(vec{10.25f, 0.f, -10.f}) * mat::scale(vec{0.15f, 4.f, 0.15f}));
  Box win2{vec{0.f, 0.f, 0.f}, BLACKISH};
  win2.transform(mat::translation(vec{10.25f, 0.f, -10.f}) * mat::scale(vec{0.15f, 0.15f, 4.f}));


  Box box3{vec{0.f, 0.f, 0.f}, WHITEISH};
  box3.transform(mat::translation(vec{8.f, -3.f, -8.f}) * mat::rotation(0.f, 0.f, 0.f) * mat::scale(vec{1.f, 2.f, 1.f}));

  Rect grass{ vec{10.f, -4.f, -40.f}, vec{10.f, -4.f, 20.f}, vec{30.f, -4.f, -40.f}, GRASS };
  Rect floor{ vec{-10.f, -4.f, -20.f}, vec{-10.f, -4.f, 0.1f}, vec{10.f, -4.f, -20.f}, FLOOR };
  Rect wall1{ vec{-10.f, -4.f, -20.f}, vec{-10.f, 8.f, -20.f}, vec{-10.f, -4.f, 0.f}, BRICKWALL };
  Rect wall2a{ vec{10.f, -4.f, 0.f}, vec{10.f, 4.f, 0.f}, vec{10.f, -4.f, -8.f}, YELLOWISH };
  Rect wall2aa{ vec{10.f, -4.f, -8.f}, vec{10.f, 4.f, -8.f}, vec{10.5f, -4.f, -8.f}, YELLOWISH };
  Rect wall2b{ vec{10.f, -4.f, -12.f}, vec{10.f, 4.f, -12.f}, vec{10.f, -4.f, -20.f}, YELLOWISH };
  Rect wall2bb{ vec{10.5f, -4.f, -12.f}, vec{10.5f, 4.f, -12.f}, vec{10.f, -4.f, -12.f}, YELLOWISH };
  Rect wall2c{ vec{10.f, 2.f, -8.f}, vec{10.f, 4.f, -8.f}, vec{10.f, 2.f, -12.f}, YELLOWISH };
  Rect wall2cc{ vec{10.5f, 2.f, -12.f}, vec{10.5f, 2.f, -8.f}, vec{10.f, 2.f, -12.f}, YELLOWISH };
  Rect wall2d{ vec{10.f, -4.f, -8.f}, vec{10.f, -2.f, -8.f}, vec{10.f, -4.f, -12.f}, YELLOWISH };
  Rect wall2dd{ vec{10.5f, -2.f, -8.f}, vec{10.5f, -2.f, -12.f}, vec{10.f, -2.f, -8.f}, YELLOWISH };
  Rect wall3{ vec{10.f, -4.f, -20.f}, vec{10.f, 8.f, -20.f}, vec{-10.f, -4.f, -20.f}, BRICKWALL };
  Rect wall4{ vec{-10.f, -4.f, 0.f}, vec{-10.f, 8.f, 0.f}, vec{10.f, -4.f, 0.f}, BRICKWALL };
  Rect cieling{ vec{-15.f, 6.f, -20.f}, vec{15.f, 6.f, -20.f}, vec{-15.f, 6.f, 0.1f}, CORRUGATED_METAL };
  cieling.transform(mat::rotation(0.f, 0.f, -PI/16.f));

  float zpos = -14.f;
  Box beam1{vec{0.f, 0.f, 0.f}, BROWNISH};
  beam1.transform(mat::translation(vec{0.f, 4.f, zpos}) * mat::rotation(0.f, 0.f, 0.f) * mat::scale(vec{30.0f, 0.5f, 0.3f}) );
  Box beam11{vec{0.f, 0.f, 0.f}, BROWNISH};
  beam11.transform(mat::translation(vec{0.f, 6.f, zpos}) * mat::rotation(0.f, 0.f, -PI/16.f) * mat::scale(vec{30.0f, 0.5f, 0.3f}) );
  Box beam12{vec{0.f, 0.f, 0.f}, BROWNISH};
  beam12.transform(mat::translation(vec{5.f, 5.f, zpos}) * mat::rotation(0.f, 0.f, PI/16.f) * mat::scale(vec{10.0f, 0.5f, 0.3f}) );
  Box beam13{vec{0.f, 0.f, 0.f}, BROWNISH};
  beam13.transform(mat::translation(vec{-5.f, 7.f, zpos}) * mat::rotation(0.f, 0.f, -PI/6.f) * mat::scale(vec{12.0f, 0.5f, 0.3f}) );
  Box beam14{vec{0.f, 0.f, 0.f}, BROWNISH};
  beam14.transform(mat::translation(vec{-5.f, 7.f, zpos}) * mat::rotation(0.f, 0.f, PI/6.f) * mat::scale(vec{12.0f, 0.5f, 0.3f}) );

  zpos = -7.f;
  Box beam2{vec{0.f, 0.f, 0.f}, BROWNISH};
  beam2.transform(mat::translation(vec{0.f, 4.f, zpos}) * mat::rotation(0.f, 0.f, 0.f) * mat::scale(vec{30.0f, 0.5f, 0.3f}) );
  Box beam21{vec{0.f, 0.f, 0.f}, BROWNISH};
  beam21.transform(mat::translation(vec{0.f, 6.f, zpos}) * mat::rotation(0.f, 0.f, -PI/16.f) * mat::scale(vec{30.0f, 0.5f, 0.3f}) );
  Box beam22{vec{0.f, 0.f, 0.f}, BROWNISH};
  beam22.transform(mat::translation(vec{5.f, 5.f, zpos}) * mat::rotation(0.f, 0.f, PI/16.f) * mat::scale(vec{10.0f, 0.5f, 0.3f}) );
  Box beam23{vec{0.f, 0.f, 0.f}, BROWNISH};
  beam23.transform(mat::translation(vec{-5.f, 7.f, zpos}) * mat::rotation(0.f, 0.f, -PI/6.f) * mat::scale(vec{12.0f, 0.5f, 0.3f}) );
  Box beam24{vec{0.f, 0.f, 0.f}, BROWNISH};
  beam24.transform(mat::translation(vec{-5.f, 7.f, zpos}) * mat::rotation(0.f, 0.f, PI/6.f) * mat::scale(vec{12.0f, 0.5f, 0.3f}) );



  Rect mirror{ vec{5.f, -3.f, -19.9f}, vec{5.f, 3.f, -19.9f}, vec{-5.f, -3.f, -19.9f}, MIRRORISH };
  Rect pic3{ vec{9.9f, 0.f, -15.f}, vec{9.9f, 3.f, -15.f}, vec{9.9f, 0.f, -19.f}, PIC3 };
  Rect pic2{ vec{9.9f, 0.f, -1.0f}, vec{9.9f, 3.f, -1.0f}, vec{9.9f, 0.f, -5.0f}, PIC2 };
  Rect pic1{ vec{9.f, -1.f, -19.9f}, vec{9.f, 3.f, -19.9f}, vec{6.f, -1.f, -19.9f}, PIC1 };
  Rect matterhorn{ vec{60.f, -10.f, -25.f}, vec{60.f, 10.f, -25.f}, vec{60.f, -10.f, -45.f}, MATTERHORN };
  Rect rocket{ vec{60.f, -10.f, 80.f}, vec{60.f, 10.f, 80.f}, vec{60.f, -10.f, 50.f}, ROCKET };


  std::unique_ptr<CompositeShape> rootShape = std::make_unique<CompositeShape>(vec{ 0.f, 0.f, 0.f }, 300.f);
  rootShape->shapes.push_back(std::make_unique<Sphere>(sphere));
  rootShape->shapes.push_back(std::make_unique<Sphere>(sphere2));
  rootShape->shapes.push_back(std::make_unique<Sphere>(sphere3));
  rootShape->shapes.push_back(std::make_unique<Sphere>(sphere4));
  rootShape->shapes.push_back(std::make_unique<Sphere>(sphere5));
  rootShape->shapes.push_back(std::move(fixture));
  rootShape->shapes.push_back(std::move(fixture2));
  rootShape->shapes.push_back(std::move(fixture3));
  rootShape->shapes.push_back(std::make_unique<Sphere>(sun));
  rootShape->shapes.push_back(std::make_unique<Rect>(pic1));
  rootShape->shapes.push_back(std::make_unique<Rect>(pic2));
  rootShape->shapes.push_back(std::make_unique<Rect>(pic3));
  rootShape->shapes.push_back(std::make_unique<Rect>(matterhorn));
  rootShape->shapes.push_back(std::make_unique<Rect>(rocket));
  rootShape->shapes.push_back(std::make_unique<Box>(box1));
  rootShape->shapes.push_back(std::make_unique<Box>(box2));
  rootShape->shapes.push_back(std::make_unique<Box>(box3));
  rootShape->shapes.push_back(std::make_unique<Box>(plank2));
  rootShape->shapes.push_back(std::make_unique<Box>(win1));
  rootShape->shapes.push_back(std::make_unique<Box>(win2));
  rootShape->shapes.push_back(std::make_unique<Box>(plank));
  rootShape->shapes.push_back(std::make_unique<Rect>(floor));
  rootShape->shapes.push_back(std::make_unique<Rect>(wall1));
  rootShape->shapes.push_back(std::make_unique<Rect>(wall2a));
  rootShape->shapes.push_back(std::make_unique<Rect>(wall2aa));
  rootShape->shapes.push_back(std::make_unique<Rect>(wall2b));
  rootShape->shapes.push_back(std::make_unique<Rect>(wall2bb));
  rootShape->shapes.push_back(std::make_unique<Rect>(wall2c));
  rootShape->shapes.push_back(std::make_unique<Rect>(wall2cc));
  rootShape->shapes.push_back(std::make_unique<Rect>(wall2d));
  rootShape->shapes.push_back(std::make_unique<Rect>(wall2dd));
  rootShape->shapes.push_back(std::make_unique<Rect>(wall3));
  rootShape->shapes.push_back(std::make_unique<Rect>(wall4));
  rootShape->shapes.push_back(std::make_unique<Rect>(cieling));
  rootShape->shapes.push_back(std::make_unique<Box>(beam1));
  rootShape->shapes.push_back(std::make_unique<Box>(beam11));
  rootShape->shapes.push_back(std::make_unique<Box>(beam12));
  rootShape->shapes.push_back(std::make_unique<Box>(beam13));
  rootShape->shapes.push_back(std::make_unique<Box>(beam14));
  rootShape->shapes.push_back(std::make_unique<Box>(beam2));
  rootShape->shapes.push_back(std::make_unique<Box>(beam21));
  rootShape->shapes.push_back(std::make_unique<Box>(beam22));
  rootShape->shapes.push_back(std::make_unique<Box>(beam23));
  rootShape->shapes.push_back(std::make_unique<Box>(beam24));
  rootShape->shapes.push_back(std::make_unique<Rect>(mirror));

  auto bunnyTris = parseMesh("bunny.off");
  std::unique_ptr<CompositeShape> bunnyShape = std::make_unique<CompositeShape>(vec{ 0.f, 0.f, 0.f }, 2.5f);
  for(auto& tri : bunnyTris) {
    bunnyShape->shapes.push_back(std::make_unique<Triangle>(tri));
  }
  bunnyShape->transform(mat::translation(vec{ 3.f, -2.f, -15.f }) * mat::rotation(0.f, 0.f, -3.f * PI / 4.f) * mat::scale(vec{ 2.f,2.f,2.f }));
  rootShape->shapes.push_back(std::move(bunnyShape));

//  auto handTris = parseMesh("hand_chair.off");
//  std::unique_ptr<CompositeShape> handShape = std::make_unique<CompositeShape>(vec{ 0.f, 0.f, 0.f }, 2000.f);
//  for(auto& tri : handTris) {
//    handShape->shapes.push_back(std::make_unique<Triangle>(tri));
//  }
//  handShape->transform(mat::translation(vec{ -5.f, -2.f, -7.f }) *  mat::rotation(0.f, 0.f, 0.f) * mat::scale(vec{ 0.002f,0.002f,0.002f }));
//  rootShape->shapes.push_back(std::move(handShape));

  return rootShape;
}
