// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class ProjCollisionQuickEditor_NoPrecompTarget : ProjCollisionQuickEditorTarget 
{
	public ProjCollisionQuickEditor_NoPrecompTarget(TargetInfo Target) : base(Target)
	{
		bUseUnityBuild = false;
		bUsePCHFiles = false;
	}
}
