\BOOKMARK [0][-]{chapter*.1}{Resume}{}% 1
\BOOKMARK [0][-]{chapter*.2}{Acknowledgments}{}% 2
\BOOKMARK [0][-]{chapter*.4}{List of Figures}{}% 3
\BOOKMARK [0][-]{chapter*.5}{List of Tables}{}% 4
\BOOKMARK [0][-]{chapter.1}{Introduction}{}% 5
\BOOKMARK [1][-]{section.1.1}{Problem Statement}{chapter.1}% 6
\BOOKMARK [1][-]{section.1.2}{Contributions}{chapter.1}% 7
\BOOKMARK [1][-]{section.1.3}{Thesis outline}{chapter.1}% 8
\BOOKMARK [0][-]{chapter.2}{Background and Related work}{}% 9
\BOOKMARK [1][-]{section.2.1}{Stereo vision}{chapter.2}% 10
\BOOKMARK [2][-]{subsection.2.1.1}{Disparity Map evaluation}{section.2.1}% 11
\BOOKMARK [1][-]{section.2.2}{GPU hardware}{chapter.2}% 12
\BOOKMARK [2][-]{subsection.2.2.1}{Nema hardware}{section.2.2}% 13
\BOOKMARK [1][-]{section.2.3}{GPU software}{chapter.2}% 14
\BOOKMARK [2][-]{subsection.2.3.1}{Programming Nema}{section.2.3}% 15
\BOOKMARK [2][-]{subsection.2.3.2}{Nema kernels}{section.2.3}% 16
\BOOKMARK [1][-]{section.2.4}{Related work}{chapter.2}% 17
\BOOKMARK [2][-]{subsection.2.4.1}{Summary}{section.2.4}% 18
\BOOKMARK [0][-]{chapter.3}{The Proposed Algorithm}{}% 19
\BOOKMARK [1][-]{section.3.1}{Algorithm requirements}{chapter.3}% 20
\BOOKMARK [1][-]{section.3.2}{Algorithm}{chapter.3}% 21
\BOOKMARK [2][-]{subsection.3.2.1}{Preprocessing}{section.3.2}% 22
\BOOKMARK [2][-]{subsection.3.2.2}{Disparity Map calculation}{section.3.2}% 23
\BOOKMARK [1][-]{section.3.3}{Optimizations}{chapter.3}% 24
\BOOKMARK [2][-]{subsection.3.3.1}{Datastructure optimization}{section.3.3}% 25
\BOOKMARK [2][-]{subsection.3.3.2}{Multithreading}{section.3.3}% 26
\BOOKMARK [2][-]{subsection.3.3.3}{Invariant code motion}{section.3.3}% 27
\BOOKMARK [2][-]{subsection.3.3.4}{SIMD}{section.3.3}% 28
\BOOKMARK [2][-]{subsection.3.3.5}{Store and reuse of XOR values}{section.3.3}% 29
\BOOKMARK [2][-]{subsection.3.3.6}{Store and reuse of partial SHD values}{section.3.3}% 30
\BOOKMARK [1][-]{section.3.4}{Optimized DM algorithm}{chapter.3}% 31
\BOOKMARK [1][-]{section.3.5}{Summary}{chapter.3}% 32
\BOOKMARK [0][-]{chapter.4}{Software Implementation Results}{}% 33
\BOOKMARK [1][-]{section.4.1}{Parameters}{chapter.4}% 34
\BOOKMARK [1][-]{section.4.2}{Functional verification results}{chapter.4}% 35
\BOOKMARK [2][-]{subsection.4.2.1}{Morphological opening window size \(MW\)}{section.4.2}% 36
\BOOKMARK [2][-]{subsection.4.2.2}{Census transform window size \(CTW\) and disparity range \(D range\)}{section.4.2}% 37
\BOOKMARK [2][-]{subsection.4.2.3}{SHD window size \(SHDW\)}{section.4.2}% 38
\BOOKMARK [1][-]{section.4.3}{Algorithm run-time performance}{chapter.4}% 39
\BOOKMARK [1][-]{section.4.4}{Summary}{chapter.4}% 40
\BOOKMARK [0][-]{chapter.5}{Implementation and evaluation of eGPU}{}% 41
\BOOKMARK [1][-]{section.5.1}{Choice of kernels}{chapter.5}% 42
\BOOKMARK [1][-]{section.5.2}{Functional Performance}{chapter.5}% 43
\BOOKMARK [1][-]{section.5.3}{Execution time}{chapter.5}% 44
\BOOKMARK [0][-]{chapter.6}{Conclusion}{}% 45
\BOOKMARK [1][-]{section.6.1}{Summary}{chapter.6}% 46
\BOOKMARK [1][-]{section.6.2}{Conclusion}{chapter.6}% 47
\BOOKMARK [1][-]{section.6.3}{Suggestions for future work}{chapter.6}% 48
\BOOKMARK [0][-]{section.6.3}{Bibliography}{}% 49
\BOOKMARK [0][-]{appendix.A}{Appendix}{}% 50
\BOOKMARK [1][-]{section.A.1}{Nema kernel for morphological erosion}{appendix.A}% 51
\BOOKMARK [1][-]{section.A.2}{Section of Nema host program invoking the eGPU}{appendix.A}% 52
