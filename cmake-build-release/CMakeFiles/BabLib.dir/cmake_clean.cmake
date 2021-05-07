file(REMOVE_RECURSE
  "libBabLib.a"
  "libBabLib.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/BabLib.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
