# Copyright 2020 Huawei Technologies Co., Ltd
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ============================================================================
"""
Test nn.Distribution.Geometric.
"""
import pytest

import mindspore.nn as nn
from mindspore import dtype
from mindspore import Tensor


def test_arguments():
    """
    Args passing during initialization.
    """
    g = nn.Geometric()
    assert isinstance(g, nn.Distribution)
    g = nn.Geometric([0.0, 0.3, 0.5, 1.0], dtype=dtype.int32)
    assert isinstance(g, nn.Distribution)

def test_prob():
    """
    Invalid probability.
    """
    with pytest.raises(ValueError):
        nn.Geometric([-0.1], dtype=dtype.int32)
    with pytest.raises(ValueError):
        nn.Geometric([1.1], dtype=dtype.int32)

class GeometricProb(nn.Cell):
    """
    Geometric distribution: initialize with probs.
    """
    def __init__(self):
        super(GeometricProb, self).__init__()
        self.g = nn.Geometric(0.5, dtype=dtype.int32)

    def construct(self, value):
        prob = self.g('prob', value)
        log_prob = self.g('log_prob', value)
        cdf = self.g('cdf', value)
        log_cdf = self.g('log_cdf', value)
        sf = self.g('survival_function', value)
        log_sf = self.g('log_survival', value)
        return prob + log_prob + cdf + log_cdf + sf + log_sf

def test_geometric_prob():
    """
    Test probability functions: passing value through construct.
    """
    net = GeometricProb()
    value = Tensor([3, 4, 5, 6, 7], dtype=dtype.float32)
    ans = net(value)
    assert isinstance(ans, Tensor)

class GeometricProb1(nn.Cell):
    """
    Geometric distribution: initialize without probs.
    """
    def __init__(self):
        super(GeometricProb1, self).__init__()
        self.g = nn.Geometric(dtype=dtype.int32)

    def construct(self, value, probs):
        prob = self.g('prob', value, probs)
        log_prob = self.g('log_prob', value, probs)
        cdf = self.g('cdf', value, probs)
        log_cdf = self.g('log_cdf', value, probs)
        sf = self.g('survival_function', value, probs)
        log_sf = self.g('log_survival', value, probs)
        return prob + log_prob + cdf + log_cdf + sf + log_sf

def test_geometric_prob1():
    """
    Test probability functions: passing value/probs through construct.
    """
    net = GeometricProb1()
    value = Tensor([3, 4, 5, 6, 7], dtype=dtype.float32)
    probs = Tensor([0.5], dtype=dtype.float32)
    ans = net(value, probs)
    assert isinstance(ans, Tensor)


class GeometricKl(nn.Cell):
    """
    Test class: kl_loss between Geometric distributions.
    """
    def __init__(self):
        super(GeometricKl, self).__init__()
        self.g1 = nn.Geometric(0.7, dtype=dtype.int32)
        self.g2 = nn.Geometric(dtype=dtype.int32)

    def construct(self, probs_b, probs_a):
        kl1 = self.g1('kl_loss', 'Geometric', probs_b)
        kl2 = self.g2('kl_loss', 'Geometric', probs_b, probs_a)
        return kl1 + kl2

def test_kl():
    """
    Test kl_loss function.
    """
    ber_net = GeometricKl()
    probs_b = Tensor([0.3], dtype=dtype.float32)
    probs_a = Tensor([0.7], dtype=dtype.float32)
    ans = ber_net(probs_b, probs_a)
    assert isinstance(ans, Tensor)

class GeometricCrossEntropy(nn.Cell):
    """
    Test class: cross_entropy of Geometric distribution.
    """
    def __init__(self):
        super(GeometricCrossEntropy, self).__init__()
        self.g1 = nn.Geometric(0.3, dtype=dtype.int32)
        self.g2 = nn.Geometric(dtype=dtype.int32)

    def construct(self, probs_b, probs_a):
        h1 = self.g1('cross_entropy', 'Geometric', probs_b)
        h2 = self.g2('cross_entropy', 'Geometric', probs_b, probs_a)
        return h1 + h2

def test_cross_entropy():
    """
    Test cross_entropy between Geometric distributions.
    """
    net = GeometricCrossEntropy()
    probs_b = Tensor([0.3], dtype=dtype.float32)
    probs_a = Tensor([0.7], dtype=dtype.float32)
    ans = net(probs_b, probs_a)
    assert isinstance(ans, Tensor)

class GeometricBasics(nn.Cell):
    """
    Test class: basic mean/sd/mode/entropy function.
    """
    def __init__(self):
        super(GeometricBasics, self).__init__()
        self.g = nn.Geometric([0.3, 0.5], dtype=dtype.int32)

    def construct(self):
        mean = self.g('mean')
        sd = self.g('sd')
        var = self.g('var')
        mode = self.g('mode')
        entropy = self.g('entropy')
        return mean + sd + var + mode + entropy

def test_bascis():
    """
    Test mean/sd/mode/entropy functionality of Geometric distribution.
    """
    net = GeometricBasics()
    ans = net()
    assert isinstance(ans, Tensor)
