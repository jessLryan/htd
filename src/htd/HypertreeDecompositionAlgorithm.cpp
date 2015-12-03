/* 
 * File:   HypertreeDecompositionAlgorithm.cpp
 *
 * Author: ABSEHER Michael (abseher@dbai.tuwien.ac.at)
 * 
 * Copyright 2015, Michael Abseher
 *    E-Mail: <abseher@dbai.tuwien.ac.at>
 * 
 * This file is part of htd.
 * 
 * htd is free software: you can redistribute it and/or modify it under 
 * the terms of the GNU General Public License as published by the Free 
 * Software Foundation, either version 3 of the License, or (at your 
 * option) any later version.
 * 
 * htd is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public 
 * License for more details.

 * You should have received a copy of the GNU General Public License
 * along with htd.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHM_CPP
#define	HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHM_CPP

#include <htd/Globals.hpp>
#include <htd/Helpers.hpp>

#include <htd/HypertreeDecompositionAlgorithm.hpp>

#include <htd/IHypertreeDecomposition.hpp>
#include <htd/IMutableHypertreeDecomposition.hpp>
#include <htd/IMutableLabeledTree.hpp>
#include <htd/ISetCoverAlgorithm.hpp>
#include <htd/VertexContainerLabel.hpp>
#include <htd/HyperedgeContainerLabel.hpp>
#include <htd/HypertreeDecompositionLabelingFunction.hpp>

#include <cstdarg>
#include <stack>
#include <vector>

htd::HypertreeDecompositionAlgorithm::HypertreeDecompositionAlgorithm(const htd::ITreeDecompositionAlgorithm & treeDecompositionAlgorithm) : treeDecompositionAlgorithm_(treeDecompositionAlgorithm)
{

}

htd::HypertreeDecompositionAlgorithm::HypertreeDecompositionAlgorithm(const htd::ITreeDecompositionAlgorithm & treeDecompositionAlgorithm, const std::vector<htd::ILabelingFunction *> & labelingFunctions) : treeDecompositionAlgorithm_(treeDecompositionAlgorithm)
{
    //TODO
    HTD_UNUSED(labelingFunctions);
}

htd::HypertreeDecompositionAlgorithm::~HypertreeDecompositionAlgorithm()
{
    
}

htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph & graph) const
{
    htd::IMutableHypertreeDecomposition * ret = nullptr;

    htd::ITreeDecomposition * treeDecomposition = treeDecompositionAlgorithm_.computeDecomposition(graph);

    if (treeDecomposition != nullptr)
    {
        ret = htd::getDefaultHypertreeDecomposition(*treeDecomposition);

        if (ret != nullptr)
        {
            htd::ISetCoverAlgorithm * setCoverAlgorithm = htd::getDefaultSetCoverAlgorithm();

            if (setCoverAlgorithm != nullptr)
            {
                htd::vertex_container vertices;

                ret->getVertices(vertices);

                htd::HypertreeDecompositionLabelingFunction hypertreeDecompositionLabelingFunction(graph, *setCoverAlgorithm);

                for (htd::vertex_t vertex : vertices)
                {
                    auto label = (dynamic_cast<const htd::VertexContainerLabel *>(ret->label(htd::bag_label_name, vertex)))->container();

                    htd::ILabel * newLabel = hypertreeDecompositionLabelingFunction.computeLabel(label);

                    ret->setLabel(hypertreeDecompositionLabelingFunction.name(), vertex, newLabel);
                }

                delete setCoverAlgorithm;
            }

            delete treeDecomposition;
        }
    }

    return ret;
}

htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph & graph, int labelingFunctionCount, ...) const
{
    va_list arguments;

    va_start(arguments, labelingFunctionCount);

    std::vector<htd::ILabelingFunction *> labelingFunctions;

    for (int labelingFunctionIndex = 0; labelingFunctionIndex < labelingFunctionCount; labelingFunctionIndex++)
    {
        labelingFunctions.push_back(va_arg(arguments, htd::ILabelingFunction *));
    }

    return computeDecomposition(graph, labelingFunctions);
}

htd::IHypertreeDecomposition * htd::HypertreeDecompositionAlgorithm::computeDecomposition(const htd::IHypergraph & graph, const std::vector<htd::ILabelingFunction *> & labelingFunctions) const
{
    htd::IMutableHypertreeDecomposition * ret = nullptr;

    htd::ITreeDecomposition * treeDecomposition = treeDecompositionAlgorithm_.computeDecomposition(graph);

    if (treeDecomposition != nullptr)
    {
        ret = htd::getDefaultHypertreeDecomposition(*treeDecomposition);

        if (ret != nullptr)
        {
            htd::ISetCoverAlgorithm * setCoverAlgorithm = htd::getDefaultSetCoverAlgorithm();

            if (setCoverAlgorithm != nullptr)
            {
                htd::vertex_container vertices;

                ret->getVertices(vertices);

                htd::HypertreeDecompositionLabelingFunction hypertreeDecompositionLabelingFunction(graph, *setCoverAlgorithm);

                for (htd::vertex_t vertex : vertices)
                {
                    auto label = (dynamic_cast<const htd::VertexContainerLabel *>(ret->label(htd::bag_label_name, vertex)))->container();

                    htd::ILabel * newLabel = hypertreeDecompositionLabelingFunction.computeLabel(label);

                    ret->setLabel(hypertreeDecompositionLabelingFunction.name(), vertex, newLabel);
                }

                delete setCoverAlgorithm;

                for (auto & labelingFunction : labelingFunctions)
                {
                    for (htd::vertex_t vertex : vertices)
                    {
                        auto label = (dynamic_cast<const htd::VertexContainerLabel *>(ret->label(htd::bag_label_name, vertex)))->container();

                        htd::ILabel * newLabel = labelingFunction->computeLabel(label);

                        ret->setLabel(labelingFunction->name(), vertex, newLabel);
                    }
                }
            }

            delete treeDecomposition;
        }
    }

    return ret;
}

#endif /* HTD_HTD_HYPERTREEDECOMPOSITIONALGORITHM_CPP */