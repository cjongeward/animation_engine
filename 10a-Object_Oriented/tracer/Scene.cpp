#include "Scene.h"
#include "Shapes.h"
#include "Settings.h"

std::vector<std::unique_ptr<Shape>> Scene::getFrame()
{
  // Assembles a room with a bunch of crap in it
  Sphere sphere{ vec{0.f, -3.f, -4.f}, MIRRORISH, 1.f };
  Sphere sphere2{ vec{7.5f, -3.f, -15.f}, BRIGHT, 1.f };
  Sphere sphere3{ vec{1.5f, -3.f, -13.f}, BRIGHT, 1.f };
  Sphere sphere4{ vec{3.5f, -3.f, -8.f}, DULL, 1.f };
  Sphere sphere5{ vec{6.5f, -3.f, -7.f}, BRIGHT, 1.f };
  Sphere light_bulb{ vec{-2.f, 3.95f, -6.f}, LIGHT, 0.25f };
  Sphere light_bulb2{ vec{2.f, 3.95f, -6.f}, LIGHT, 0.25f };
  Sphere sun{ vec{200.f, 80.f, 60.f}, SUN, 0.25f };

  Box box1{vec{0.f, 0.f, 0.f}, BRIGHT};
  box1.transform(mat::translation(vec{-7.f, -3.f, -17.f}) * mat::scale(vec{2.f, 2.f, 2.f}));

  Box win1{vec{0.f, 0.f, 0.f}, BLACKISH};
  win1.transform(mat::translation(vec{10.25f, 0.f, -10.f}) * mat::scale(vec{0.15f, 4.f, 0.15f}));
  Box win2{vec{0.f, 0.f, 0.f}, BLACKISH};
  win2.transform(mat::translation(vec{10.25f, 0.f, -10.f}) * mat::scale(vec{0.15f, 0.15f, 4.f}));

  Box plank{vec{0.f, 0.f, 0.f}, BROWNISH};
  plank.transform(mat::translation(vec{9.5f, -0.5f, -3.f}) * mat::scale(vec{1.0f, 0.15f, 6.f}) );

  Box box2{vec{0.f, 0.f, 0.f}, WHITEISH};
  box2.transform(mat::translation(vec{0.f, -3.f, -6.f}) * mat::rotation(PI4, 0.f, 0.f) * mat::scale(vec{1.f, 2.f, 1.f}));
  Box box3{vec{0.f, 0.f, 0.f}, WHITEISH};
  box3.transform(mat::translation(vec{3.f, -3.f, -9.f}) * mat::rotation(PI4, 0.f, 0.f) * mat::scale(vec{1.f, 2.f, 1.f}));
  Box plank2{vec{0.f, 0.f, 0.f}, BROWNISH};
  plank2.transform(mat::translation(vec{1.5f, -1.93, -7.5f}) * mat::rotation(-PI4, 0.f, 0.f) * mat::scale(vec{1.0f, 0.15f, 6.f}) );

  Rect grass{ vec{10.f, -4.f, -40.f}, vec{10.f, -4.f, 20.f}, vec{30.f, -4.f, -40.f}, GRASS };
  Rect floor{ vec{-10.f, -4.f, -20.f}, vec{-10.f, -4.f, 0.1f}, vec{10.f, -4.f, -20.f}, FLOOR };
  Rect wall1{ vec{-10.f, -4.f, -20.f}, vec{-10.f, 4.f, -20.f}, vec{-10.f, -4.f, 0.f}, YELLOWISH };
  Rect wall2a{ vec{10.f, -4.f, 0.f}, vec{10.f, 4.f, 0.f}, vec{10.f, -4.f, -8.f}, YELLOWISH };
  Rect wall2aa{ vec{10.f, -4.f, -8.f}, vec{10.f, 4.f, -8.f}, vec{10.5f, -4.f, -8.f}, YELLOWISH };
  Rect wall2b{ vec{10.f, -4.f, -12.f}, vec{10.f, 4.f, -12.f}, vec{10.f, -4.f, -20.f}, YELLOWISH };
  Rect wall2bb{ vec{10.5f, -4.f, -12.f}, vec{10.5f, 4.f, -12.f}, vec{10.f, -4.f, -12.f}, YELLOWISH };
  Rect wall2c{ vec{10.f, 2.f, -8.f}, vec{10.f, 4.f, -8.f}, vec{10.f, 2.f, -12.f}, YELLOWISH };
  Rect wall2cc{ vec{10.5f, 2.f, -12.f}, vec{10.5f, 2.f, -8.f}, vec{10.f, 2.f, -12.f}, YELLOWISH };
  Rect wall2d{ vec{10.f, -4.f, -8.f}, vec{10.f, -2.f, -8.f}, vec{10.f, -4.f, -12.f}, YELLOWISH };
  Rect wall2dd{ vec{10.5f, -2.f, -8.f}, vec{10.5f, -2.f, -12.f}, vec{10.f, -2.f, -8.f}, YELLOWISH };
  Rect wall3{ vec{10.f, -4.f, -20.f}, vec{10.f, 4.f, -20.f}, vec{-10.f, -4.f, -20.f}, YELLOWISH };
  Rect wall4{ vec{-10.f, -4.f, 0.f}, vec{-10.f, 4.f, 0.f}, vec{10.f, -4.f, 0.f}, YELLOWISH };
  Rect cieling{ vec{-10.f, 4.f, -20.f}, vec{10.f, 4.f, -20.f}, vec{-10.f, 4.f, 0.1f}, WHITEISH };
  Rect mirror{ vec{5.f, -3.f, -19.9f}, vec{5.f, 3.f, -19.9f}, vec{-5.f, -3.f, -19.9f}, MIRRORISH };
  Rect pic3{ vec{9.9f, 0.f, -15.f}, vec{9.9f, 3.f, -15.f}, vec{9.9f, 0.f, -19.f}, PIC3 };
  Rect pic2{ vec{9.9f, 0.f, -1.0f}, vec{9.9f, 3.f, -1.0f}, vec{9.9f, 0.f, -5.0f}, PIC2 };
  Rect pic1{ vec{9.f, -1.f, -19.9f}, vec{9.f, 3.f, -19.9f}, vec{6.f, -1.f, -19.9f}, PIC1 };

  Bunny bunny{ vec{0.f, 0.f, 0.f}, WHITEISH};

  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.push_back(std::make_unique<Sphere>(sphere));
  shapes.push_back(std::make_unique<Sphere>(sphere2));
  shapes.push_back(std::make_unique<Sphere>(sphere3));
  shapes.push_back(std::make_unique<Sphere>(sphere4));
  shapes.push_back(std::make_unique<Sphere>(sphere5));
  shapes.push_back(std::make_unique<Sphere>(light_bulb));
  shapes.push_back(std::make_unique<Sphere>(light_bulb2));
  shapes.push_back(std::make_unique<Sphere>(sun));
  shapes.push_back(std::make_unique<Rect>(pic1));
  shapes.push_back(std::make_unique<Rect>(pic2));
  shapes.push_back(std::make_unique<Rect>(pic3));
  shapes.push_back(std::make_unique<Box>(box1));
  shapes.push_back(std::make_unique<Box>(box2));
  shapes.push_back(std::make_unique<Box>(box3));
  shapes.push_back(std::make_unique<Box>(plank2));
  shapes.push_back(std::make_unique<Box>(win1));
  shapes.push_back(std::make_unique<Box>(win2));
  shapes.push_back(std::make_unique<Box>(plank));
  shapes.push_back(std::make_unique<Rect>(grass));
  shapes.push_back(std::make_unique<Rect>(floor));
  shapes.push_back(std::make_unique<Rect>(wall1));
  shapes.push_back(std::make_unique<Rect>(wall2a));
  shapes.push_back(std::make_unique<Rect>(wall2aa));
  shapes.push_back(std::make_unique<Rect>(wall2b));
  shapes.push_back(std::make_unique<Rect>(wall2bb));
  shapes.push_back(std::make_unique<Rect>(wall2c));
  shapes.push_back(std::make_unique<Rect>(wall2cc));
  shapes.push_back(std::make_unique<Rect>(wall2d));
  shapes.push_back(std::make_unique<Rect>(wall2dd));
  shapes.push_back(std::make_unique<Rect>(wall3));
  shapes.push_back(std::make_unique<Rect>(wall4));
  shapes.push_back(std::make_unique<Rect>(cieling));
  shapes.push_back(std::make_unique<Rect>(mirror));
  shapes.push_back(std::make_unique<Bunny>(bunny));
  return shapes;
}
