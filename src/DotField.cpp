//
// Created by Matthew F Tang on 30/5/2024.
//

#include "../include/DotField.h"

#include <cmath>

#include "../include/Dot.h"

void
DotField::Make (const DotFieldParams &params)
{
  auto n_coherent = static_cast<int> (
    std::floor (static_cast<float> (params.n_dots) * params.coherence));
  //  number of coherent dots
  dots_.clear ();
  float dir;
  for (int i = 0; i < params.n_dots; i++)
    {
      if (i < n_coherent)
	{
	  // assigns the coherent dots the global direction
	  dir = params.direction; // gives the dot the global direction
	}
      else
	{
	  dir = GenerateRandomFloat (0, PI * 2); // gives dot random direction
	}
      Dot dot;
      dot.Make (params.aperture, dir, params.speed, params.radius, params.color,
		params.centre_location);
      dots_.push_back (dot);
    }
}

// loop through all the dots in field and draw them
void
DotField::Run ()
{
  for (auto &dot : dots_)
    {
      dot.Draw ();
    }
}

float
DotField::GenerateRandomFloat (const float min, const float max)
{
  std::uniform_real_distribution<float> dist (min, max);
  return dist (gen_);
}
DotField::DotField () : gen_ (rd_ ()) {}
