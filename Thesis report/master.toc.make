\select@language {german}
\select@language {USenglish}
\contentsline {chapter}{Resume}{ii}{chapter*.1}
\contentsline {chapter}{Acknowledgments}{iv}{chapter*.2}
\contentsline {chapter}{List of Figures}{xii}{chapter*.4}
\contentsline {chapter}{List of Tables}{xiv}{chapter*.5}
\contentsline {chapter}{\numberline {1}Introduction}{1}{chapter.1}
\contentsline {section}{\numberline {1.1}Problem Statement}{2}{section.1.1}
\contentsline {section}{\numberline {1.2}Contributions}{2}{section.1.2}
\contentsline {section}{\numberline {1.3}Thesis outline}{3}{section.1.3}
\contentsline {chapter}{\numberline {2}Background and Related work}{5}{chapter.2}
\contentsline {section}{\numberline {2.1}Stereo vision}{5}{section.2.1}
\contentsline {subsection}{\numberline {2.1.1}Disparity Map evaluation}{8}{subsection.2.1.1}
\contentsline {section}{\numberline {2.2}GPU hardware}{8}{section.2.2}
\contentsline {subsection}{\numberline {2.2.1}Nema hardware}{8}{subsection.2.2.1}
\contentsline {section}{\numberline {2.3}GPU software}{9}{section.2.3}
\contentsline {subsection}{\numberline {2.3.1}Programming Nema}{10}{subsection.2.3.1}
\contentsline {subsection}{\numberline {2.3.2}Nema kernels}{11}{subsection.2.3.2}
\contentsline {section}{\numberline {2.4}Related work}{12}{section.2.4}
\contentsline {subsection}{\numberline {2.4.1}Summary}{13}{subsection.2.4.1}
\contentsline {chapter}{\numberline {3}The Proposed Algorithm}{15}{chapter.3}
\contentsline {section}{\numberline {3.1}Algorithm requirements}{15}{section.3.1}
\contentsline {section}{\numberline {3.2}Algorithm}{16}{section.3.2}
\contentsline {subsection}{\numberline {3.2.1}Preprocessing}{17}{subsection.3.2.1}
\contentsline {subsection}{\numberline {3.2.2}Disparity Map calculation}{18}{subsection.3.2.2}
\contentsline {section}{\numberline {3.3}Optimizations}{19}{section.3.3}
\contentsline {subsection}{\numberline {3.3.1}Datastructure optimization}{19}{subsection.3.3.1}
\contentsline {subsection}{\numberline {3.3.2}Multithreading}{20}{subsection.3.3.2}
\contentsline {subsection}{\numberline {3.3.3}Invariant code motion}{20}{subsection.3.3.3}
\contentsline {subsection}{\numberline {3.3.4}SIMD}{21}{subsection.3.3.4}
\contentsline {subsection}{\numberline {3.3.5}Store and reuse of XOR values}{21}{subsection.3.3.5}
\contentsline {subsection}{\numberline {3.3.6}Store and reuse of partial SHD values}{22}{subsection.3.3.6}
\contentsline {section}{\numberline {3.4}Optimized DM algorithm}{23}{section.3.4}
\contentsline {section}{\numberline {3.5}Summary}{23}{section.3.5}
\contentsline {chapter}{\numberline {4}Software Implementation Results}{25}{chapter.4}
\contentsline {section}{\numberline {4.1}Parameters}{25}{section.4.1}
\contentsline {section}{\numberline {4.2}Functional verification results}{25}{section.4.2}
\contentsline {subsection}{\numberline {4.2.1}Morphological opening window size (MW)}{26}{subsection.4.2.1}
\contentsline {subsection}{\numberline {4.2.2}Census transform window size (CTW) and disparity range (D range)}{26}{subsection.4.2.2}
\contentsline {subsection}{\numberline {4.2.3}SHD window size (SHDW)}{29}{subsection.4.2.3}
\contentsline {section}{\numberline {4.3}Algorithm run-time performance}{29}{section.4.3}
\contentsline {section}{\numberline {4.4}Summary}{32}{section.4.4}
\contentsline {chapter}{\numberline {5}Implementation and evaluation of eGPU}{33}{chapter.5}
\contentsline {section}{\numberline {5.1}Choice of kernels}{33}{section.5.1}
\contentsline {section}{\numberline {5.2}Functional Performance}{34}{section.5.2}
\contentsline {section}{\numberline {5.3}Execution time}{35}{section.5.3}
\contentsline {chapter}{\numberline {6}Conclusion}{39}{chapter.6}
\contentsline {section}{\numberline {6.1}Summary}{39}{section.6.1}
\contentsline {section}{\numberline {6.2}Conclusion}{39}{section.6.2}
\contentsline {section}{\numberline {6.3}Suggestions for future work}{40}{section.6.3}
\contentsline {chapter}{Bibliography}{41}{section.6.3}
\contentsline {chapter}{\numberline {A}Appendix}{45}{appendix.A}
\contentsline {section}{\numberline {A.1}Nema kernel for morphological erosion}{45}{section.A.1}
\contentsline {section}{\numberline {A.2}Section of Nema host program invoking the eGPU}{46}{section.A.2}
