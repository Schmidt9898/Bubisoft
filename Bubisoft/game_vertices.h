#ifndef GAME_VERTICES_H_INCLUDED
#define GAME_VERTICES_H_INCLUDED

/*format: x, y, z, u, v*/

/*
90 floats
18 entries
6 triangles
*/
float floor_triangles[] = {
6, 0, 0, 0.984676, 0.507769,
0, 6, 0, 0.496048, 0.968275,
-6, 0, 0, 0.0270223, 0.494526,
-6, 0, 0, 0.0269359, 0.494573,
-5, -5, 0, 0.0951472, 0.0892107,
0, -6, 0, 0.50321, 0.0290741,
0, -6, 0, 0.50336, 0.0291614,
5, -5, 0, 0.896304, 0.0765297,
6, 0, 0, 0.984709, 0.507598,
6, 0, 0, 0.984666, 0.507966,
5, 5, 0, 0.951753, 0.908694,
0, 6, 0, 0.496105, 0.96813,
0, 6, 0, 0.49613, 0.967875,
-5, 5, 0, 0.0515758, 0.91245,
-6, 0, 0, 0.0269588, 0.494417,
-6, 0, 0, 0.026839, 0.494543,
0, -6, 0, 0.503267, 0.0291924,
6, 0, 0, 0.98445, 0.507773
};


/*
15 floats
3 entries
1 triangle
*/
float pickup_vertices[] = {
    0.0f, 0.05f, 0.0f, 0.0f, 0.0f,
    0.045f, 0.0f, 0.f, 1.0f, 0.0f,
    -0.045f, 0.0f, 0.0f, 1.0f, 1.0f
};




/*
900 floats
180 entries
60 triangles
*/
float grass_triangles[] = {

-0.068978, -0.0252111, -0.764459, 0.509885, 0.546319,
-0.0421937, 0.0172055, -1.46521, 0.511057, 0.548919,
-0.0464868, -0.0123354, -1.46521, 0.511116, 0.548825,
-0.0598051, 0.0373405, -0.763159, 0.519428, 0.54477,
-0.0155752, 0.0232089, -1.46521, 0.51096, 0.548675,
-0.0421937, 0.0172055, -1.46521, 0.511057, 0.548919,
-0.0194287, -0.0205219, -1.46521, 0.51113, 0.548723,
-0.068978, -0.0252111, -0.764459, 0.509885, 0.546319,
-0.0464868, -0.0123354, -1.46521, 0.511116, 0.548825,
0.0224782, -0.000528601, -0.762834, 0.507215, 0.555101,
-0.0194287, -0.0205219, -1.46521, 0.51113, 0.548723,
-0.00247562, -0.000457492, -1.46521, 0.510902, 0.548645,
-0.00449127, 0.0498156, -0.763017, 0.511321, 0.544388,
-0.00247562, -0.000457492, -1.46521, 0.510902, 0.548645,
-0.0155752, 0.0232089, -1.46521, 0.51096, 0.548675,
-0.32258, -0.194922, -0.60984, 0.497913, 0.391269,
-0.218117, 0.184198, -1.46522, 0.525416, 0.51376,
-0.268084, -0.159623, -1.46522, 0.512293, 0.500681,
-0.259888, 0.232591, -0.600952, 0.621583, 0.478498,
0.0916896, 0.254069, -1.46522, 0.521072, 0.525804,
-0.218117, 0.184198, -1.46522, 0.525416, 0.51376,
0.0468405, -0.254904, -1.46522, 0.503812, 0.512753,
-0.32258, -0.194922, -0.60984, 0.497913, 0.391269,
-0.268084, -0.159623, -1.46522, 0.512293, 0.500681,
0.302484, -0.0262281, -0.598732, 0.441451, 0.6088,
0.0468405, -0.254904, -1.46522, 0.503812, 0.512753,
0.244153, -0.0213789, -1.46522, 0.506346, 0.526394,
0.0916896, 0.254069, -1.46522, 0.521072, 0.525804,
0.302484, -0.0262281, -0.598732, 0.441451, 0.6088,
0.244153, -0.0213789, -1.46522, 0.506346, 0.526394,
-0.068978, -0.0252111, -0.764459, 0.509885, 0.546319,
-0.346004, 0.31054, -0.467894, 0.789837, 0.5119,
-0.0598051, 0.0373405, -0.763159, 0.519428, 0.54477,
-0.0127505, -0.0422228, -0.757942, 0.514253, 0.555108,
-0.429979, -0.262106, -0.479799, 0.53872, 0.263525,
-0.068978, -0.0252111, -0.764459, 0.509885, 0.546319,
-0.00449127, 0.0498156, -0.763017, 0.511321, 0.544388,
-0.346004, 0.31054, -0.467894, 0.789837, 0.5119,
0.160382, 0.424747, -0.466595, 0.642473, 0.794742,
-0.00449127, 0.0498156, -0.763017, 0.511321, 0.544388,
0.407283, -0.036143, -0.464921, 0.313265, 0.744802,
0.0224782, -0.000528601, -0.762834, 0.507215, 0.555101,
-0.0127505, -0.0422228, -0.757942, 0.514253, 0.555108,
0.407283, -0.036143, -0.464921, 0.313265, 0.744802,
0.0847709, -0.417845, -0.420138, 0.259669, 0.438768,
-0.32258, -0.194922, -0.60984, 0.497913, 0.391269,
-0.451934, 0.412143, -0.648974, 0.760405, 0.430945,
-0.259888, 0.232591, -0.600952, 0.621583, 0.478498,
-0.32258, -0.194922, -0.60984, 0.497913, 0.391269,
0.120982, -0.556586, -0.58546, 0.223642, 0.413185,
-0.563619, -0.349458, -0.664808, 0.494007, 0.235226,
0.118158, 0.317853, -0.599982, 0.594368, 0.614299,
-0.451934, 0.412143, -0.648974, 0.760405, 0.430945,
0.221544, 0.564035, -0.647246, 0.715935, 0.743924,
0.118158, 0.317853, -0.599982, 0.594368, 0.614299,
0.549913, -0.0489348, -0.645019, 0.355101, 0.735349,
0.302484, -0.0262281, -0.598732, 0.441451, 0.6088,
0.302484, -0.0262281, -0.598732, 0.441451, 0.6088,
0.120982, -0.556586, -0.58546, 0.223642, 0.413185,
0.0617102, -0.31119, -0.5653, 0.384857, 0.474194,
0.221544, 0.564035, -0.647246, 0.715935, 0.743924,
0.782295, -0.0704421, -0.947157, 0.226746, 0.932415,
0.549913, -0.0489348, -0.645019, 0.355101, 0.735349,
0.549913, -0.0489348, -0.645019, 0.355101, 0.735349,
0.179875, -0.783423, -0.863508, -0.00286645, 0.325268,
0.120982, -0.556586, -0.58546, 0.223642, 0.413185,
-0.563619, -0.349458, -0.664808, 0.494007, 0.235226,
-0.624768, 0.577127, -0.952711, 0.949475, 0.358024,
-0.451934, 0.412143, -0.648974, 0.760405, 0.430945,
-0.563619, -0.349458, -0.664808, 0.494007, 0.235226,
0.179875, -0.783423, -0.863508, -0.00286645, 0.325268,
-0.781626, -0.492518, -0.974949, 0.504745, 0.0236799,
0.221544, 0.564035, -0.647246, 0.715935, 0.743924,
-0.624768, 0.577127, -0.952711, 0.949475, 0.358024,
0.32111, 0.790454, -0.950284, 0.892183, 0.932415,
0.0847709, -0.417845, -0.420138, 0.259669, 0.438768,
-0.607069, -0.540068, -0.696606, 0.48632, 0.00995445,
-0.429979, -0.262106, -0.479799, 0.53872, 0.263525,
-0.346004, 0.31054, -0.467894, 0.789837, 0.5119,
0.157719, 0.737367, -0.674899, 0.843191, 0.972617,
0.160382, 0.424747, -0.466595, 0.642473, 0.794742,
0.160382, 0.424747, -0.466595, 0.642473, 0.794742,
0.686291, 0.0595866, -0.672147, 0.217808, 0.972617,
0.407283, -0.036143, -0.464921, 0.313265, 0.744802,
0.407283, -0.036143, -0.464921, 0.313265, 0.744802,
0.270297, -0.648763, -0.59853, 0.024431, 0.407164,
0.0847709, -0.417845, -0.420138, 0.259669, 0.438768,
-0.429979, -0.262106, -0.479799, 0.53872, 0.263525,
-0.630786, 0.411072, -0.677035, 0.997605, 0.397633,
-0.346004, 0.31054, -0.467894, 0.789837, 0.5119,
-0.068978, -0.0252111, -0.764459, 0.509885, 0.546319,
-0.0598051, 0.0373405, -0.763159, 0.519428, 0.54477,
-0.0421937, 0.0172055, -1.46521, 0.511057, 0.548919,
-0.0598051, 0.0373405, -0.763159, 0.519428, 0.54477,
-0.00449127, 0.0498156, -0.763017, 0.511321, 0.544388,
-0.0155752, 0.0232089, -1.46521, 0.51096, 0.548675,
-0.0194287, -0.0205219, -1.46521, 0.51113, 0.548723,
-0.0127505, -0.0422228, -0.757942, 0.514253, 0.555108,
-0.068978, -0.0252111, -0.764459, 0.509885, 0.546319,
0.0224782, -0.000528601, -0.762834, 0.507215, 0.555101,
-0.0127505, -0.0422228, -0.757942, 0.514253, 0.555108,
-0.0194287, -0.0205219, -1.46521, 0.51113, 0.548723,
-0.00449127, 0.0498156, -0.763017, 0.511321, 0.544388,
0.0224782, -0.000528601, -0.762834, 0.507215, 0.555101,
-0.00247562, -0.000457492, -1.46521, 0.510902, 0.548645,
-0.32258, -0.194922, -0.60984, 0.497913, 0.391269,
-0.259888, 0.232591, -0.600952, 0.621583, 0.478498,
-0.218117, 0.184198, -1.46522, 0.525416, 0.51376,
-0.259888, 0.232591, -0.600952, 0.621583, 0.478498,
0.118158, 0.317853, -0.599982, 0.594368, 0.614299,
0.0916896, 0.254069, -1.46522, 0.521072, 0.525804,
0.0468405, -0.254904, -1.46522, 0.503812, 0.512753,
0.0617102, -0.31119, -0.5653, 0.384857, 0.474194,
-0.32258, -0.194922, -0.60984, 0.497913, 0.391269,
0.302484, -0.0262281, -0.598732, 0.441451, 0.6088,
0.0617102, -0.31119, -0.5653, 0.384857, 0.474194,
0.0468405, -0.254904, -1.46522, 0.503812, 0.512753,
0.0916896, 0.254069, -1.46522, 0.521072, 0.525804,
0.118158, 0.317853, -0.599982, 0.594368, 0.614299,
0.302484, -0.0262281, -0.598732, 0.441451, 0.6088,
-0.068978, -0.0252111, -0.764459, 0.509885, 0.546319,
-0.429979, -0.262106, -0.479799, 0.53872, 0.263525,
-0.346004, 0.31054, -0.467894, 0.789837, 0.5119,
-0.0127505, -0.0422228, -0.757942, 0.514253, 0.555108,
0.0847709, -0.417845, -0.420138, 0.259669, 0.438768,
-0.429979, -0.262106, -0.479799, 0.53872, 0.263525,
-0.00449127, 0.0498156, -0.763017, 0.511321, 0.544388,
-0.0598051, 0.0373405, -0.763159, 0.519428, 0.54477,
-0.346004, 0.31054, -0.467894, 0.789837, 0.5119,
-0.00449127, 0.0498156, -0.763017, 0.511321, 0.544388,
0.160382, 0.424747, -0.466595, 0.642473, 0.794742,
0.407283, -0.036143, -0.464921, 0.313265, 0.744802,
-0.0127505, -0.0422228, -0.757942, 0.514253, 0.555108,
0.0224782, -0.000528601, -0.762834, 0.507215, 0.555101,
0.407283, -0.036143, -0.464921, 0.313265, 0.744802,
-0.32258, -0.194922, -0.60984, 0.497913, 0.391269,
-0.563619, -0.349458, -0.664808, 0.494007, 0.235226,
-0.451934, 0.412143, -0.648974, 0.760405, 0.430945,
-0.32258, -0.194922, -0.60984, 0.497913, 0.391269,
0.0617102, -0.31119, -0.5653, 0.384857, 0.474194,
0.120982, -0.556586, -0.58546, 0.223642, 0.413185,
0.118158, 0.317853, -0.599982, 0.594368, 0.614299,
-0.259888, 0.232591, -0.600952, 0.621583, 0.478498,
-0.451934, 0.412143, -0.648974, 0.760405, 0.430945,
0.118158, 0.317853, -0.599982, 0.594368, 0.614299,
0.221544, 0.564035, -0.647246, 0.715935, 0.743924,
0.549913, -0.0489348, -0.645019, 0.355101, 0.735349,
0.302484, -0.0262281, -0.598732, 0.441451, 0.6088,
0.549913, -0.0489348, -0.645019, 0.355101, 0.735349,
0.120982, -0.556586, -0.58546, 0.223642, 0.413185,
0.221544, 0.564035, -0.647246, 0.715935, 0.743924,
0.32111, 0.790454, -0.950284, 0.892183, 0.932415,
0.782295, -0.0704421, -0.947157, 0.226746, 0.932415,
0.549913, -0.0489348, -0.645019, 0.355101, 0.735349,
0.782295, -0.0704421, -0.947157, 0.226746, 0.932415,
0.179875, -0.783423, -0.863508, -0.00286645, 0.325268,
-0.563619, -0.349458, -0.664808, 0.494007, 0.235226,
-0.781626, -0.492518, -0.974949, 0.504745, 0.0236799,
-0.624768, 0.577127, -0.952711, 0.949475, 0.358024,
-0.563619, -0.349458, -0.664808, 0.494007, 0.235226,
0.120982, -0.556586, -0.58546, 0.223642, 0.413185,
0.179875, -0.783423, -0.863508, -0.00286645, 0.325268,
0.221544, 0.564035, -0.647246, 0.715935, 0.743924,
-0.451934, 0.412143, -0.648974, 0.760405, 0.430945,
-0.624768, 0.577127, -0.952711, 0.949475, 0.358024,
0.0847709, -0.417845, -0.420138, 0.259669, 0.438768,
0.270297, -0.648763, -0.59853, 0.024431, 0.407164,
-0.607069, -0.540068, -0.696606, 0.48632, 0.00995445,
-0.346004, 0.31054, -0.467894, 0.789837, 0.5119,
-0.630786, 0.411072, -0.677035, 0.997605, 0.397633,
0.157719, 0.737367, -0.674899, 0.843191, 0.972617,
0.160382, 0.424747, -0.466595, 0.642473, 0.794742,
0.157719, 0.737367, -0.674899, 0.843191, 0.972617,
0.686291, 0.0595866, -0.672147, 0.217808, 0.972617,
0.407283, -0.036143, -0.464921, 0.313265, 0.744802,
0.686291, 0.0595866, -0.672147, 0.217808, 0.972617,
0.270297, -0.648763, -0.59853, 0.024431, 0.407164,
-0.429979, -0.262106, -0.479799, 0.53872, 0.263525,
-0.607069, -0.540068, -0.696606, 0.48632, 0.00995445,
-0.630786, 0.411072, -0.677035, 0.997605, 0.397633
};

/*
1020 floats
204 entries
68 triangles
*/
float slime_vertices[] = {
0, 0.884384, 0.474649, 0.329989, 0.781571,
0.242781, 0.586124, 0.799072, 0.471989, 0.693196,
0.338439, 0.817064, 0.474649, 0.449463, 0.828061,
0, 0.266361, 1.01584, 0.465852, 0.563126,
0, 0, 1.03741, 0.504876, 0.500598,
0.101932, 0.246086, 1.01584, 0.492886, 0.573063,
6.57472e-007, 1, 0.0919654, 0.24244, 0.931741,
0.338439, 0.817064, 0.474649, 0.449463, 0.828061,
0.382683, 0.92388, 0.0919654, 0.4228, 0.992886,
0, 0.266361, 1.01584, 0.465852, 0.563126,
0.242781, 0.586124, 0.799072, 0.471989, 0.693196,
0, 0.634416, 0.799072, 0.401371, 0.664873,
0.242781, 0.586124, 0.799072, 0.471989, 0.693196,
0.625354, 0.625354, 0.474649, 0.576775, 0.821945,
0.338439, 0.817064, 0.474649, 0.449463, 0.828061,
0.101932, 0.246086, 1.01584, 0.492886, 0.573063,
0, 0, 1.03741, 0.504876, 0.500598,
0.188346, 0.188346, 1.01584, 0.521426, 0.571858,
0.338439, 0.817064, 0.474649, 0.449463, 0.828061,
0.707107, 0.707107, 0.0919654, 0.612335, 0.991116,
0.382683, 0.92388, 0.0919654, 0.4228, 0.992886,
0.101932, 0.246086, 1.01584, 0.492886, 0.573063,
0.4486, 0.4486, 0.799072, 0.54813, 0.689409,
0.242781, 0.586124, 0.799072, 0.471989, 0.693196,
0.625354, 0.625354, 0.474649, 0.576775, 0.821945,
0.923879, 0.382683, 0.0919654, 0.79457, 0.915529,
0.707107, 0.707107, 0.0919654, 0.612335, 0.991116,
0.4486, 0.4486, 0.799072, 0.54813, 0.689409,
0.246086, 0.101932, 1.01584, 0.547688, 0.560447,
0.586124, 0.242781, 0.799072, 0.616458, 0.657844,
0.4486, 0.4486, 0.799072, 0.54813, 0.689409,
0.817064, 0.338439, 0.474649, 0.6919, 0.768425,
0.625354, 0.625354, 0.474649, 0.576775, 0.821945,
0.188346, 0.188346, 1.01584, 0.521426, 0.571858,
0, 0, 1.03741, 0.504876, 0.500598,
0.246086, 0.101932, 1.01584, 0.547688, 0.560447,
0.246086, 0.101932, 1.01584, 0.547688, 0.560447,
0.634416, 0, 0.799072, 0.666731, 0.603186,
0.586124, 0.242781, 0.799072, 0.616458, 0.657844,
0.586124, 0.242781, 0.799072, 0.616458, 0.657844,
0.884384, 0, 0.474649, 0.783536, 0.677982,
0.817064, 0.338439, 0.474649, 0.6919, 0.768425,
0.246086, 0.101932, 1.01584, 0.547688, 0.560447,
0, 0, 1.03741, 0.504876, 0.500598,
0.266361, 1.40798e-007, 1.01584, 0.567056, 0.53951,
0.923879, 0.382683, 0.0919654, 0.79457, 0.915529,
0.884384, 0, 0.474649, 0.783536, 0.677982,
1, 0, 0.0919654, 0.926377, 0.769537,
-0.101932, 0.246086, 1.01584, 0.444599, 0.543563,
0, 0.266361, 1.01584, 0.465852, 0.563126,
0, 0.634416, 0.799072, 0.401371, 0.664873,
-0.382683, 0.92388, 0.0919654, 0.0918206, 0.801873,
-0.338439, 0.817064, 0.474649, 0.235224, 0.692411,
0, 0.884384, 0.474649, 0.329989, 0.781571,
0.884384, 0, 0.474649, 0.783536, 0.677982,
0.586124, -0.24278, 0.799072, 0.695279, 0.533982,
0.817064, -0.338439, 0.474649, 0.829412, 0.557031,
0.266361, 1.40798e-007, 1.01584, 0.567056, 0.53951,
0, 0, 1.03741, 0.504876, 0.500598,
0.246086, -0.101932, 1.01584, 0.577016, 0.512782,
-0.338439, 0.817064, 0.474649, 0.235224, 0.692411,
-0.24278, 0.586124, 0.799072, 0.348165, 0.612389,
0, 0.634416, 0.799072, 0.401371, 0.664873,
-0.707106, 0.707107, 0.0919654, 9.96287e-005, 0.615871,
-0.625353, 0.625354, 0.474649, 0.183488, 0.572946,
-0.338439, 0.817064, 0.474649, 0.235224, 0.692411,
0.884384, 0, 0.474649, 0.783536, 0.677982,
0.923879, -0.382683, 0.0919654, 0.99897, 0.591844,
1, 0, 0.0919654, 0.926377, 0.769537,
0.266361, 1.40798e-007, 1.01584, 0.567056, 0.53951,
0.586124, -0.24278, 0.799072, 0.695279, 0.533982,
0.634416, 0, 0.799072, 0.666731, 0.603186,
0.246086, -0.101932, 1.01584, 0.577016, 0.512782,
0, 0, 1.03741, 0.504876, 0.500598,
0.188346, -0.188346, 1.01584, 0.576718, 0.484147,
-0.448599, 0.4486, 0.799072, 0.316284, 0.54478,
-0.24278, 0.586124, 0.799072, 0.348165, 0.612389,
-0.338439, 0.817064, 0.474649, 0.235224, 0.692411,
-0.448599, 0.4486, 0.799072, 0.316284, 0.54478,
-0.188346, 0.188346, 1.01584, 0.432979, 0.517123,
-0.101932, 0.246086, 1.01584, 0.444599, 0.543563,
0.817064, -0.338439, 0.474649, 0.829412, 0.557031,
0.707106, -0.707107, 0.0919654, 0.9999, 0.397087,
0.923879, -0.382683, 0.0919654, 0.99897, 0.591844,
0.586124, -0.24278, 0.799072, 0.695279, 0.533982,
0.188346, -0.188346, 1.01584, 0.576718, 0.484147,
0.4486, -0.4486, 0.799072, 0.695337, 0.458001,
-0.586124, 0.242781, 0.799072, 0.31297, 0.46903,
-0.448599, 0.4486, 0.799072, 0.316284, 0.54478,
-0.625353, 0.625354, 0.474649, 0.183488, 0.572946,
-0.586124, 0.242781, 0.799072, 0.31297, 0.46903,
-0.246086, 0.101932, 1.01584, 0.43238, 0.488344,
-0.188346, 0.188346, 1.01584, 0.432979, 0.517123,
0.817064, -0.338439, 0.474649, 0.829412, 0.557031,
0.4486, -0.4486, 0.799072, 0.695337, 0.458001,
0.625354, -0.625354, 0.474649, 0.826699, 0.42973,
-0.817064, 0.338439, 0.474649, 0.177232, 0.443429,
-0.625353, 0.625354, 0.474649, 0.183488, 0.572946,
-0.707106, 0.707107, 0.0919654, 9.96287e-005, 0.615871,
0.625354, -0.625354, 0.474649, 0.826699, 0.42973,
0.382683, -0.923879, 0.0919654, 0.924897, 0.212288,
0.707106, -0.707107, 0.0919654, 0.9999, 0.397087,
0.188346, -0.188346, 1.01584, 0.576718, 0.484147,
0.24278, -0.586124, 0.799072, 0.663508, 0.388794,
0.4486, -0.4486, 0.799072, 0.695337, 0.458001,
-0.634416, 4.61491e-007, 0.799072, 0.339474, 0.396842,
-0.266361, 2.23772e-007, 1.01584, 0.442912, 0.461661,
-0.246086, 0.101932, 1.01584, 0.43238, 0.488344,
-0.884383, 5.0522e-007, 0.474649, 0.222734, 0.32097,
-0.817064, 0.338439, 0.474649, 0.177232, 0.443429,
-0.923879, 0.382684, 0.0919654, 9.9719e-005, 0.409201,
0.4486, -0.4486, 0.799072, 0.695337, 0.458001,
0.338439, -0.817064, 0.474649, 0.77496, 0.314131,
0.625354, -0.625354, 0.474649, 0.826699, 0.42973,
0.188346, -0.188346, 1.01584, 0.576718, 0.484147,
0, 0, 1.03741, 0.504876, 0.500598,
0.101932, -0.246085, 1.01584, 0.564755, 0.458069,
-0.634416, 4.61491e-007, 0.799072, 0.339474, 0.396842,
-0.586124, 0.242781, 0.799072, 0.31297, 0.46903,
-0.817064, 0.338439, 0.474649, 0.177232, 0.443429,
-0.246086, -0.101932, 1.01584, 0.462371, 0.440566,
-0.266361, 2.23772e-007, 1.01584, 0.442912, 0.461661,
-0.634416, 4.61491e-007, 0.799072, 0.339474, 0.396842,
-0.923879, -0.382683, 0.0919654, 0.212201, 0.0766038,
-0.817064, -0.338439, 0.474649, 0.316346, 0.229989,
-0.884383, 5.0522e-007, 0.474649, 0.222734, 0.32097,
0.24278, -0.586124, 0.799072, 0.663508, 0.388794,
-2.84893e-007, -0.884383, 0.474649, 0.68572, 0.221595,
0.338439, -0.817064, 0.474649, 0.77496, 0.314131,
0.101932, -0.246085, 1.01584, 0.564755, 0.458069,
0, 0, 1.03741, 0.504876, 0.500598,
0, -0.266361, 1.01584, 0.543777, 0.438682,
-0.817064, -0.338439, 0.474649, 0.316346, 0.229989,
-0.586124, -0.24278, 0.799072, 0.393794, 0.343256,
-0.634416, 4.61491e-007, 0.799072, 0.339474, 0.396842,
-0.4486, -0.448599, 0.799072, 0.46181, 0.311762,
-0.586124, -0.24278, 0.799072, 0.393794, 0.343256,
-0.817064, -0.338439, 0.474649, 0.316346, 0.229989,
0.382683, -0.923879, 0.0919654, 0.924897, 0.212288,
-2.84893e-007, -0.884383, 0.474649, 0.68572, 0.221595,
-3.26005e-007, -1, 0.0919654, 0.779423, 0.0784525,
0.101932, -0.246085, 1.01584, 0.564755, 0.458069,
-2.40163e-007, -0.634416, 0.799072, 0.608069, 0.336519,
0.24278, -0.586124, 0.799072, 0.663508, 0.388794,
-0.188346, -0.188346, 1.01584, 0.48845, 0.428569,
-0.246086, -0.101932, 1.01584, 0.462371, 0.440566,
-0.586124, -0.24278, 0.799072, 0.393794, 0.343256,
-2.40163e-007, -0.634416, 0.799072, 0.608069, 0.336519,
-0.338439, -0.817064, 0.474649, 0.564842, 0.174728,
-2.84893e-007, -0.884383, 0.474649, 0.68572, 0.221595,
0, -0.266361, 1.01584, 0.543777, 0.438682,
0, 0, 1.03741, 0.504876, 0.500598,
-0.101932, -0.246085, 1.01584, 0.517213, 0.428128,
-0.625354, -0.625353, 0.474649, 0.43517, 0.176877,
-0.817064, -0.338439, 0.474649, 0.316346, 0.229989,
-0.923879, -0.382683, 0.0919654, 0.212201, 0.0766038,
-0.242781, -0.586124, 0.799072, 0.537147, 0.309425,
-0.4486, -0.448599, 0.799072, 0.46181, 0.311762,
-0.625354, -0.625353, 0.474649, 0.43517, 0.176877,
-2.84893e-007, -0.884383, 0.474649, 0.68572, 0.221595,
-0.382684, -0.923879, 0.0919654, 0.601137, 0.00309151,
-3.26005e-007, -1, 0.0919654, 0.779423, 0.0784525,
-2.40163e-007, -0.634416, 0.799072, 0.608069, 0.336519,
-0.101932, -0.246085, 1.01584, 0.517213, 0.428128,
-0.242781, -0.586124, 0.799072, 0.537147, 0.309425,
-0.242781, -0.586124, 0.799072, 0.537147, 0.309425,
-0.101932, -0.246085, 1.01584, 0.517213, 0.428128,
-0.188346, -0.188346, 1.01584, 0.48845, 0.428569,
-0.338439, -0.817064, 0.474649, 0.564842, 0.174728,
-0.625354, -0.625353, 0.474649, 0.43517, 0.176877,
-0.707107, -0.707106, 0.0919654, 0.40236, 9.96287e-005,
-2.40163e-007, -0.634416, 0.799072, 0.608069, 0.336519,
0, -0.266361, 1.01584, 0.543777, 0.438682,
-0.101932, -0.246085, 1.01584, 0.517213, 0.428128,
-0.338439, -0.817064, 0.474649, 0.564842, 0.174728,
-0.707107, -0.707106, 0.0919654, 0.40236, 9.96287e-005,
-0.382684, -0.923879, 0.0919654, 0.601137, 0.00309151,
-0.242781, -0.586124, 0.799072, 0.537147, 0.309425,
-0.188346, -0.188346, 1.01584, 0.48845, 0.428569,
-0.4486, -0.448599, 0.799072, 0.46181, 0.311762,
-2.84893e-007, -0.884383, 0.474649, 0.68572, 0.221595,
-0.338439, -0.817064, 0.474649, 0.564842, 0.174728,
-0.382684, -0.923879, 0.0919654, 0.601137, 0.00309151,
-2.40163e-007, -0.634416, 0.799072, 0.608069, 0.336519,
-0.242781, -0.586124, 0.799072, 0.537147, 0.309425,
-0.338439, -0.817064, 0.474649, 0.564842, 0.174728,
-0.242781, -0.586124, 0.799072, 0.537147, 0.309425,
-0.625354, -0.625353, 0.474649, 0.43517, 0.176877,
-0.338439, -0.817064, 0.474649, 0.564842, 0.174728,
-0.101932, -0.246085, 1.01584, 0.517213, 0.428128,
0, 0, 1.03741, 0.504876, 0.500598,
-0.188346, -0.188346, 1.01584, 0.48845, 0.428569,
-0.625354, -0.625353, 0.474649, 0.43517, 0.176877,
-0.923879, -0.382683, 0.0919654, 0.212201, 0.0766038,
-0.707107, -0.707106, 0.0919654, 0.40236, 9.96287e-005,
-0.188346, -0.188346, 1.01584, 0.48845, 0.428569,
-0.586124, -0.24278, 0.799072, 0.393794, 0.343256,
-0.4486, -0.448599, 0.799072, 0.46181, 0.311762,
0.101932, -0.246085, 1.01584, 0.564755, 0.458069,
0, -0.266361, 1.01584, 0.543777, 0.438682,
-2.40163e-007, -0.634416, 0.799072, 0.608069, 0.336519,
0.382683, -0.923879, 0.0919654, 0.924897, 0.212288,
0.338439, -0.817064, 0.474649, 0.77496, 0.314131,
-2.84893e-007, -0.884383, 0.474649, 0.68572, 0.221595,
-0.4486, -0.448599, 0.799072, 0.46181, 0.311762,
-0.817064, -0.338439, 0.474649, 0.316346, 0.229989,
-0.625354, -0.625353, 0.474649, 0.43517, 0.176877,
-0.188346, -0.188346, 1.01584, 0.48845, 0.428569,
0, 0, 1.03741, 0.504876, 0.500598,
-0.246086, -0.101932, 1.01584, 0.462371, 0.440566,
0.24278, -0.586124, 0.799072, 0.663508, 0.388794,
-2.40163e-007, -0.634416, 0.799072, 0.608069, 0.336519,
-2.84893e-007, -0.884383, 0.474649, 0.68572, 0.221595,
0.4486, -0.4486, 0.799072, 0.695337, 0.458001,
0.24278, -0.586124, 0.799072, 0.663508, 0.388794,
0.338439, -0.817064, 0.474649, 0.77496, 0.314131,
0.188346, -0.188346, 1.01584, 0.576718, 0.484147,
0.101932, -0.246085, 1.01584, 0.564755, 0.458069,
0.24278, -0.586124, 0.799072, 0.663508, 0.388794,
0.625354, -0.625354, 0.474649, 0.826699, 0.42973,
0.338439, -0.817064, 0.474649, 0.77496, 0.314131,
0.382683, -0.923879, 0.0919654, 0.924897, 0.212288,
-0.817064, -0.338439, 0.474649, 0.316346, 0.229989,
-0.634416, 4.61491e-007, 0.799072, 0.339474, 0.396842,
-0.884383, 5.0522e-007, 0.474649, 0.222734, 0.32097,
-0.246086, -0.101932, 1.01584, 0.462371, 0.440566,
0, 0, 1.03741, 0.504876, 0.500598,
-0.266361, 2.23772e-007, 1.01584, 0.442912, 0.461661,
0.817064, -0.338439, 0.474649, 0.829412, 0.557031,
0.586124, -0.24278, 0.799072, 0.695279, 0.533982,
0.4486, -0.4486, 0.799072, 0.695337, 0.458001,
0.586124, -0.24278, 0.799072, 0.695279, 0.533982,
0.246086, -0.101932, 1.01584, 0.577016, 0.512782,
0.188346, -0.188346, 1.01584, 0.576718, 0.484147,
-0.923879, -0.382683, 0.0919654, 0.212201, 0.0766038,
-0.884383, 5.0522e-007, 0.474649, 0.222734, 0.32097,
-1, 6.0754e-007, 0.0919654, 0.0758916, 0.226124,
-0.246086, -0.101932, 1.01584, 0.462371, 0.440566,
-0.634416, 4.61491e-007, 0.799072, 0.339474, 0.396842,
-0.586124, -0.24278, 0.799072, 0.393794, 0.343256,
-0.634416, 4.61491e-007, 0.799072, 0.339474, 0.396842,
-0.817064, 0.338439, 0.474649, 0.177232, 0.443429,
-0.884383, 5.0522e-007, 0.474649, 0.222734, 0.32097,
-0.266361, 2.23772e-007, 1.01584, 0.442912, 0.461661,
0, 0, 1.03741, 0.504876, 0.500598,
-0.246086, 0.101932, 1.01584, 0.43238, 0.488344,
0.817064, -0.338439, 0.474649, 0.829412, 0.557031,
0.625354, -0.625354, 0.474649, 0.826699, 0.42973,
0.707106, -0.707107, 0.0919654, 0.9999, 0.397087,
0.266361, 1.40798e-007, 1.01584, 0.567056, 0.53951,
0.246086, -0.101932, 1.01584, 0.577016, 0.512782,
0.586124, -0.24278, 0.799072, 0.695279, 0.533982,
-0.884383, 5.0522e-007, 0.474649, 0.222734, 0.32097,
-0.923879, 0.382684, 0.0919654, 9.9719e-005, 0.409201,
-1, 6.0754e-007, 0.0919654, 0.0758916, 0.226124,
-0.634416, 4.61491e-007, 0.799072, 0.339474, 0.396842,
-0.246086, 0.101932, 1.01584, 0.43238, 0.488344,
-0.586124, 0.242781, 0.799072, 0.31297, 0.46903,
0.884384, 0, 0.474649, 0.783536, 0.677982,
0.817064, -0.338439, 0.474649, 0.829412, 0.557031,
0.923879, -0.382683, 0.0919654, 0.99897, 0.591844,
0.884384, 0, 0.474649, 0.783536, 0.677982,
0.634416, 0, 0.799072, 0.666731, 0.603186,
0.586124, -0.24278, 0.799072, 0.695279, 0.533982,
0.923879, 0.382683, 0.0919654, 0.79457, 0.915529,
0.817064, 0.338439, 0.474649, 0.6919, 0.768425,
0.884384, 0, 0.474649, 0.783536, 0.677982,
0.586124, 0.242781, 0.799072, 0.616458, 0.657844,
0.634416, 0, 0.799072, 0.666731, 0.603186,
0.884384, 0, 0.474649, 0.783536, 0.677982,
-0.817064, 0.338439, 0.474649, 0.177232, 0.443429,
-0.707106, 0.707107, 0.0919654, 9.96287e-005, 0.615871,
-0.923879, 0.382684, 0.0919654, 9.9719e-005, 0.409201,
-0.586124, 0.242781, 0.799072, 0.31297, 0.46903,
-0.188346, 0.188346, 1.01584, 0.432979, 0.517123,
-0.448599, 0.4486, 0.799072, 0.316284, 0.54478,
0.246086, 0.101932, 1.01584, 0.547688, 0.560447,
0.266361, 1.40798e-007, 1.01584, 0.567056, 0.53951,
0.634416, 0, 0.799072, 0.666731, 0.603186,
0.4486, 0.4486, 0.799072, 0.54813, 0.689409,
0.586124, 0.242781, 0.799072, 0.616458, 0.657844,
0.817064, 0.338439, 0.474649, 0.6919, 0.768425,
-0.586124, 0.242781, 0.799072, 0.31297, 0.46903,
-0.625353, 0.625354, 0.474649, 0.183488, 0.572946,
-0.817064, 0.338439, 0.474649, 0.177232, 0.443429,
-0.246086, 0.101932, 1.01584, 0.43238, 0.488344,
0, 0, 1.03741, 0.504876, 0.500598,
-0.188346, 0.188346, 1.01584, 0.432979, 0.517123,
-0.448599, 0.4486, 0.799072, 0.316284, 0.54478,
-0.101932, 0.246086, 1.01584, 0.444599, 0.543563,
-0.24278, 0.586124, 0.799072, 0.348165, 0.612389,
0.4486, 0.4486, 0.799072, 0.54813, 0.689409,
0.188346, 0.188346, 1.01584, 0.521426, 0.571858,
0.246086, 0.101932, 1.01584, 0.547688, 0.560447,
0.625354, 0.625354, 0.474649, 0.576775, 0.821945,
0.817064, 0.338439, 0.474649, 0.6919, 0.768425,
0.923879, 0.382683, 0.0919654, 0.79457, 0.915529,
-0.448599, 0.4486, 0.799072, 0.316284, 0.54478,
-0.338439, 0.817064, 0.474649, 0.235224, 0.692411,
-0.625353, 0.625354, 0.474649, 0.183488, 0.572946,
-0.188346, 0.188346, 1.01584, 0.432979, 0.517123,
0, 0, 1.03741, 0.504876, 0.500598,
-0.101932, 0.246086, 1.01584, 0.444599, 0.543563,
0.101932, 0.246086, 1.01584, 0.492886, 0.573063,
0.188346, 0.188346, 1.01584, 0.521426, 0.571858,
0.4486, 0.4486, 0.799072, 0.54813, 0.689409,
0.338439, 0.817064, 0.474649, 0.449463, 0.828061,
0.625354, 0.625354, 0.474649, 0.576775, 0.821945,
0.707107, 0.707107, 0.0919654, 0.612335, 0.991116,
-0.707106, 0.707107, 0.0919654, 9.96287e-005, 0.615871,
-0.338439, 0.817064, 0.474649, 0.235224, 0.692411,
-0.382683, 0.92388, 0.0919654, 0.0918206, 0.801873,
0.242781, 0.586124, 0.799072, 0.471989, 0.693196,
0.4486, 0.4486, 0.799072, 0.54813, 0.689409,
0.625354, 0.625354, 0.474649, 0.576775, 0.821945,
0, 0.266361, 1.01584, 0.465852, 0.563126,
0.101932, 0.246086, 1.01584, 0.492886, 0.573063,
0.242781, 0.586124, 0.799072, 0.471989, 0.693196,
-0.338439, 0.817064, 0.474649, 0.235224, 0.692411,
0, 0.634416, 0.799072, 0.401371, 0.664873,
0, 0.884384, 0.474649, 0.329989, 0.781571,
-0.101932, 0.246086, 1.01584, 0.444599, 0.543563,
0, 0, 1.03741, 0.504876, 0.500598,
0, 0.266361, 1.01584, 0.465852, 0.563126,
6.57472e-007, 1, 0.0919654, 0.24244, 0.931741,
0, 0.884384, 0.474649, 0.329989, 0.781571,
0.338439, 0.817064, 0.474649, 0.449463, 0.828061,
0, 0.884384, 0.474649, 0.329989, 0.781571,
0, 0.634416, 0.799072, 0.401371, 0.664873,
0.242781, 0.586124, 0.799072, 0.471989, 0.693196,
-0.382683, 0.92388, 0.0919654, 0.0918206, 0.801873,
0, 0.884384, 0.474649, 0.329989, 0.781571,
6.57472e-007, 1, 0.0919654, 0.24244, 0.931741,
-0.101932, 0.246086, 1.01584, 0.444599, 0.543563,
0, 0.634416, 0.799072, 0.401371, 0.664873,
-0.24278, 0.586124, 0.799072, 0.348165, 0.612389
};

/*
30 floats
6 entries
2 triangles
*/

float screen_background[] = {
    -1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, +1.0f, 0.0f, 0.0f, 0.0f,
    +1.0f, +1.0f, 0.0f, 1.0f, 0.0f,

    +1.0f, +1.0f, 0.0f, 1.0f, 0.0f,
    +1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f, 1.0f
};

float slider_vertices[] = {
    0.0f, 0.03f, 0.0f, 0.0f, 0.0f,
    -0.02f, -0.03f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    +0.02f, -0.03f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.03f, 0.0f, 1.0f, 1.0f
};


/*
150 floats
30 entries
10 triangles
*/
float button_vertices[] = {

-1, 1, 1, 0.0617403, 0.0609527,
3.53649, -1, 1, 0.9457, 0.924208,
3.53649, 1, 1, 0.948822, 0.0603014,
3.53649, 1, 1, 0.979362, 0.0126852,
3.53649, -1, -1, 0.00704902, 0.147363,
3.53649, 1, -1, 0.985764, 0.146272,
3.53649, -1, 1, 0.989934, 0.00473875,
-1, -1, -1, 0.0132512, 0.117267,
3.53649, -1, -1, 0.984296, 0.117266,
-1, -1, -1, 0.0132512, 0.0938291,
-1, 1, 1, 0.978816, 0.0116574,
-1, 1, -1, 0.992266, 0.11788,
3.53649, 1, 1, 0.97826, 0.122042,
-1, 1, -1, 0.00789153, 0.0163172,
-1, 1, 1, 0.025691, 0.105407,
-1, 1, 1, 0.0617403, 0.0609527,
-1, -1, 1, 0.059099, 0.923644,
3.53649, -1, 1, 0.9457, 0.924208,
3.53649, 1, 1, 0.979362, 0.0126852,
3.53649, -1, 1, 0.00314832, 0.0241524,
3.53649, -1, -1, 0.00704902, 0.147363,
3.53649, -1, 1, 0.989934, 0.00473875,
-1, -1, 1, 0.0061152, 0.0115423,
-1, -1, -1, 0.0132512, 0.117267,
-1, -1, -1, 0.0132512, 0.0938291,
-1, -1, 1, 0.0061152, 0.00372982,
-1, 1, 1, 0.978816, 0.0116574,
3.53649, 1, 1, 0.97826, 0.122042,
3.53649, 1, -1, 0.994561, 0.00850487,
-1, 1, -1, 0.00789153, 0.0163172
};





#endif // GAME_VERTICES_H_INCLUDED
