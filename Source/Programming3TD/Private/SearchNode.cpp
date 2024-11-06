// Fill out your copyright notice in the Description page of Project Settings.


#include "SearchNode.h"
#include <Logging/StructuredLog.h>

SearchNode::SearchNode(TObjectPtr<AGraphNode> state, TObjectPtr<AGraphNode> endNode, int64 ID, TObjectPtr<SearchNode> parent) // parent is nullptr in .h file
{
	if (parent == this)
	{
		UE_LOG(LogTemp, Warning, TEXT("Parent is the same as the child"));
	}
	State = state;

	if (Parent) {

		UE_LOGFMT(LogTemp, Warning, "Parent before setting: `{0}`", Parent->State.GetName());
	}
	else {

		UE_LOGFMT(LogTemp, Warning, "Parent before setting: NONE");
	}

	if (parent) {
		UE_LOGFMT(LogTemp, Warning, "Parent input: `{0}`", parent->State.GetName());
	}
	else {
		UE_LOGFMT(LogTemp, Warning, "Parent input: NONE");
	}

	Parent = parent;

	if (parent) {
		UE_LOGFMT(LogTemp, Warning, "Parent after setting: `{0}`", parent->State.GetName());
	}
	else {
		UE_LOGFMT(LogTemp, Warning, "Parent after setting: NONE");
	}

	Identity = ID;
	SetEndNode(endNode);
	
	
	if (!parent)
	{
		throw;
	}
	else
	{
		
		Depth = parent->Depth + 1;

		float ParentCost = Parent->GetCost();
		float DistanceCost = FVector::Dist(State->GetActorLocation(), Parent->State->GetActorLocation());
		float ThreatLevelCost = State->GetThreatLevel();
		Cost = ParentCost + DistanceCost + ThreatLevelCost;
	}

	if (Parent) {
		UE_LOGFMT(LogTemp, Warning, "This: `{0}`, This Depth `{1}`, This ID `{2}`. Parent: `{3}`, Parent Depth `{4}`, Parent ID `{5}`", state->GetName(), Depth, Identity, Parent->State->GetName(), Parent->Depth, Parent->Identity);
	}
	else {
		UE_LOGFMT(LogTemp, Warning, "This: `{0}`, This Depth `{1}`, This ID `{2}`. Parent: NONE", state->GetName(), Depth, Identity);
	}
}

SearchNode::SearchNode(TObjectPtr<AGraphNode> state, TObjectPtr<AGraphNode> endNode, int64 ID)
{

	State = state;

	Parent = nullptr;

	Identity = ID;
	SetEndNode(endNode);

	Depth = 0;
	Cost = state->GetThreatLevel();

}

void SearchNode::SetEndNode(TObjectPtr<AGraphNode> endNode)
{
	Heuristic = FVector::Dist(State->GetActorLocation(), endNode->GetActorLocation());
}

float SearchNode::GetCost() const
{
	return Cost;
}

float SearchNode::GetExpectedCost() const
{
	return GetCost() + Heuristic;
}

TDeque<TObjectPtr<AGraphNode>> SearchNode::GetPath() const
{
	TDeque<TObjectPtr<AGraphNode>> path;
	path.PushLast(State);

	if (Depth != 0)
	{
		Parent->MakePath(path);
	}

	return path;
}

void SearchNode::MakePath(TDeque<TObjectPtr<AGraphNode>> &path) const
{
	path.PushFirst(State);

	if (Depth == 0)
	{
		return;
	}
	Parent->MakePath(path);
}

