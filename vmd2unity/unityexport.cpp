#include "stdafx.h"
#include "unityexport.h"
#include <iostream>
#include <fstream>

void UnityExporter::Export(VMD_MOTION_DATA& data, std::string path, std::string name, int fps) {
	std::cout << "Exporting... ";
	std::ofstream strm(path + "\\" + name + ".anim", std::ios::out | std::ios::binary);
	std::string ss = R"(%YAML 1.1
%TAG !u!tag:unity3d.com, 2011 :
    -- - !u!74 & 7400000
    AnimationClip :
    m_ObjectHideFlags : 0
    m_PrefabParentObject : {fileID: 0}
m_PrefabInternal: {fileID: 0}
m_Name: )";
	std::string ss2 = R"(
    serializedVersion : 6
    m_Legacy : 0
    m_Compressed : 0
    m_UseHighQualityCurve : 1
    m_RotationCurves : 
)";
	strm << ss << name << ss2;
	std::string crv1 = R"(  - curve:
      serializedVersion: 2
      m_Curve:
)";
	std::string tm0 = "      - time: ";
	std::string tm1 = R"(
        value: {)";
	std::string tm2 = R"(}
        inSlope: {x: 0, y: 0, z: 0, w: 0}
        outSlope: {x: 0, y: 0, z: 0, w: 0}
        tangentMode: 0
)";
	std::string crv2 = R"(      m_PreInfinity: 2
      m_PostInfinity: 2
      m_RotationOrder: 4
    path: )";

	for (auto& a : data.keyframes_n) {
		if (!a.second[0]->bone) continue;
		strm << crv1;
		for (auto& b : a.second) {
			strm << tm0 << std::to_string(((float)b->frame) / fps) << tm1;
			strm << "x: " << std::to_string(b->rotation.x) << ", y: " << std::to_string(b->rotation.y) << ", z: " << std::to_string(b->rotation.z) << ", w: " << std::to_string(b->rotation.w);
			strm << tm2;
		}
		strm << crv2 << a.second[0]->bone->fullName << "\n";
	}

	std::string ss3 = R"(  m_CompressedRotationCurves: []
  m_EulerCurves: []
  m_PositionCurves:
)";
	strm << ss3;
	tm2 = R"(}
        inSlope: {x: 0, y: 0, z: 0}
        outSlope: {x: 0, y: 0, z: 0}
        tangentMode: 0
)";
	for (auto& a : data.keyframes_n) {
		if (!a.second[0]->bone) continue;
		strm << crv1;
		for (auto& b : a.second) {
			strm << tm0 << std::to_string(((float)b->frame) / fps) << tm1;
			strm << "x: " << std::to_string(b->position.x) << ", y: " << std::to_string(b->position.y) << ", z: " << std::to_string(b->position.z);
			strm << tm2;
		}
		strm << crv2 << a.second[0]->bone->fullName << "\n";
	}
	std::string ss4 = R"(m_ScaleCurves: []
  m_FloatCurves: []
  m_PPtrCurves: []
  m_SampleRate: 24
  m_WrapMode: 0
  m_Bounds:
    m_Center: {x: 0, y: 0, z: 0}
    m_Extent: {x: 0, y: 0, z: 0}
  m_ClipBindingConstant:
    genericBindings: []
    pptrCurveMapping: []
  m_AnimationClipSettings:
    serializedVersion: 2
    m_AdditiveReferencePoseClip: {fileID: 0}
    m_AdditiveReferencePoseTime: 0
    m_StartTime: 0
    m_StopTime: )", ss5 = R"(
    m_OrientationOffsetY: 0
    m_Level: 0
    m_CycleOffset: 0
    m_HasAdditiveReferencePose: 0
    m_LoopTime: 0
    m_LoopBlend: 0
    m_LoopBlendOrientation: 0
    m_LoopBlendPositionY: 0
    m_LoopBlendPositionXZ: 0
    m_KeepOriginalOrientation: 0
    m_KeepOriginalPositionY: 1
    m_KeepOriginalPositionXZ: 0
    m_HeightFromFeet: 0
    m_Mirror: 0
  m_EditorCurves: []
  m_EulerEditorCurves: []
  m_HasGenericRootTransform: 0
  m_HasMotionFloatCurves: 0
  m_GenerateMotionCurves: 0
  m_Events: []
)";
	strm << ss4 << std::to_string(((float)data.keyframes.back().frame) / fps) << ss5;
	std::cout << "done" << std::endl;
}