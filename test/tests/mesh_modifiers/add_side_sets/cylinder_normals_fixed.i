[Mesh]
  type = FileMesh
  file = cylinder.e
  # This MeshModifier currently only works with SerialMesh.
  # For more information, refer to #2129.
  distribution = serial
[]

# Mesh Modifiers
[MeshModifiers]
  [./add_side_sets]
    type = SideSetsFromNormals
    normals = '0  1  0
               0 -1  0'
    new_boundary = 'front back'

    # This parameter makes it so that we won't
    # adjust the normal for each adjacent element.
    fixed_normal = true

    variance = 0.5
  [../]
[]

[Variables]
  [./u]
  [../]
[]

[Kernels]
  [./diff]
    type = Diffusion
    variable = u
  [../]
[]

[BCs]
  [./front]
    type = DirichletBC
    variable = u
    boundary = front
    value = 0
  [../]
  [./back]
    type = DirichletBC
    variable = u
    boundary = back
    value = 1
  [../]
[]

[Executioner]
  type = Steady

  # Preconditioned JFNK (default)
  solve_type = 'PJFNK'

  petsc_options_iname = '-pc_type -pc_hypre_type'
  petsc_options_value = 'hypre boomeramg'
[]

[Outputs]
  exodus = true
  output_on = 'initial timestep_end'
  [./console]
    type = Console
    perf_log = true
    output_on = 'timestep_end failed nonlinear linear'
  [../]
[]
