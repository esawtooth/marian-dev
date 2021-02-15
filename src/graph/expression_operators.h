#pragma once
#include "graph/expression_graph.h"
#include "graph/node_initializers.h"

namespace marian {
/**
 * @defgroup graph_ops Expression Graph Operators
 *
 * @{
 */

Expr debug(Expr a, const std::string& message = "");

Expr checkpoint(Expr a);

typedef Expr(ActivationFunction)(Expr);

typedef std::function<void(Expr, const std::vector<Expr>&)> LambdaNodeFunctor;
Expr lambda(const std::vector<Expr>&, Shape, Type, LambdaNodeFunctor);
Expr lambda(const std::vector<Expr>&, Shape, Type, LambdaNodeFunctor, LambdaNodeFunctor);

/**
 * @addtogroup graph_ops_activation Activation Functions
 * @ingroup graph_ops
 * @brief Provides various activation functions for use in the expression
 *
 * @{
*/
/**
 * @brief Linear Activation Function
 *
 * Returns @p nodes[0]
 */
Expr plus(const std::vector<Expr>& nodes);

/**
 * @brief Logistic Activation Function
 *
 * Computes the <a href="https://en.wikipedia.org/wiki/Logistic_function">logistic function</a>
 * of the given expression
 *
 * @todo rename sigmoid to logistic
 */
Expr sigmoid(Expr a);

/**
 * @copybrief sigmoid
 * @warning not implemented
 */
Expr sigmoid(const std::vector<Expr>& nodes);

/**
 * @brief Swish node
 *
 * Computes the Swish activation function with \f$\beta=1 \f$
 * \f[
 *    \operatorname{swish}(x) = x \cdot \operatorname{sigmoid}(\beta x)
 * \f]
 *
 * @see SwishNodeOp
 */
Expr swish(Expr a);

/**
 * @copybrief swish
 * @warning not implemented for @p nodes of size > 1
 * @returns swish(nodes[0])
 */
Expr swish(const std::vector<Expr>& nodes);

/**
 * @brief Gaussian Error Linear Unit (GELU)
 *
 * Computes an _approxmiation_ to the Gaussian Error Linear Unit
 * \f[
 *    \operatorname{gelu}(x) = x \cdot \Phi(x)
 *      = x \cdot \frac{1}{2}\left[
 *         1 + \operatorname{erf}\left(\frac{x}{\sqrt{2}}\right)
 *      \right]
 *      \sim \operatorname{swish}(x, 1.702)
 * \f]
 *
 * using @ref SwishNodeOp(a, 1.702)
 * @see SwishNodeOp
 */
Expr gelu(Expr a);

/**
 * @copybrief gelu
 * @warning not implemented for @p nodes of size > 1
 * @returns gelu(nodes[0])
 */
Expr gelu(const std::vector<Expr>&);

/**
 * @brief Tanh
 *
 * @see TanhNodeOp
 */
Expr tanh(const std::vector<Expr>& nodes);

/**
 * @copybrief tanh
 * Convience function to put parameter pack @p Args into a Expr vector
 */
template <typename... Args>
Expr tanh(Args... args) {
  std::vector<Expr> nodes{args...};
  return tanh(nodes);
}

/**
 * @brief Rectified Linear Unit (ReLU)
 *
 * Computes the ReLU activation for the Expr
 * @see ReLUNodeOp
 */
Expr relu(Expr a);

/**
 * @copybrief relu
 * @warning not implemented for @p nodes of size > 1
 * @returns relu(nodes[0])
 */
Expr relu(const std::vector<Expr>& nodes);

/**
 * @brief Leaky ReLU (LeakyReLU)
 *
 * Computes the <a href="https://en.wikipedia.org/wiki/Rectifier_(neural_networks)#LeakyReLU">
 * LeakyReLU</a> activation for the expression
 * Activation function:
 * \f[
 *   \operatorname{leakyrelu}(x) =
 *   \begin{cases}
 *     0.01x & \text{if } x \leq 0 \\
 *     x & \text{if } x > 0
 *   \end{cases}
 * \f]

 * @see PReLUNodeOp
 */
Expr leakyrelu(Expr a);

/**
 * @copybrief leakyrelu
 * @warning not implemented
 */
Expr leakyrelu(const std::vector<Expr>& nodes);

/**
 * @brief Parametric Rectified Linear Unit (PReLU)
 *
 * Computes the <a href="https://en.wikipedia.org/wiki/Rectifier_(neural_networks)#Parametric_ReLU">
 * Parametric ReLU</a> activation for the expression
 * \f[
 *   \operatorname{leakyrelu}(x) =
 *   \begin{cases}
 *     \alpha x & \text{if } x \leq 0 \\
 *     x & \text{if } x > 0
 *   \end{cases}
 * \f]

 * @see PReLUNodeOp
 * @note @p alpha is **not** trainable.
 */
Expr prelu(Expr a, float alpha = 0.01);

/**
 * @copybrief prelu
 * @warning not implemented
 */
Expr prelu(const std::vector<Expr>&, float alpha = 0.01);
/** @} */

/**
 * @addtogroup graph_ops_mathematical Mathematical
 * @ingroup graph_ops
 * @brief Performs mathematical operations in the expression graph
 *
 * @{
*/
/**
 * @name Exponentiation and Logarithmic functions
 * @{
 */
/**
* @brief Natural logarithm
*
* Computes the element-wise natural logarithm of the expression: \f$ \log(a) \f$
* @see LogNodeOp
*/
Expr log(Expr a);

/**
 * @brief Natural exponentiation
 *
 * Computes the element-wise natural logarithm of the expression: \f$ e^a \f$
 * @see ExpNodeOp
 */
Expr exp(Expr a);
/** @} */

/**
 * @name Trigonometric functions
 * @{
 */
/**
* @brief Sine
*
* Computes the element-wise sine of the expression: \f$ \sin(a) \f$
* @see SinNodeOp
*/
Expr sin(Expr a);

/**
* @brief Cosine
*
* Computes the element-wise cosine of the expression: \f$ \cos(a) \f$
* @see CosNodeOp
*/
Expr cos(Expr a);

/**
* @brief Tangent
*
* Computes the element-wise tangent of the expression: \f$ \tan(a) \f$
* @see TanNodeOp
*/
Expr tan(Expr a);
/** @} */
/** @} */


/**
 * @addtogroup graph_ops_arithmetic Arithmetic
 * @ingroup graph_ops
 * @brief Performs arithmetic in the expression graph
 *
 * @{
*/

/**
 * Returns \f$ -a \f$
 * @see NegNodeOp for implementation.
 */
///@{
Expr operator-(Expr a);
///@}

/*********************************************************/

/**
 * @name Addition
 * @brief Performs \f$ a + b \f$ in the expression graph
 *
 * @{
*/
Expr operator+(Expr a, Expr b);   //!< @see Implementation in PlusNodeOp
Expr operator+(float a, Expr b);  //!< @see Implementation in ScalarAddNodeOp
Expr operator+(Expr a, float b);  //!< @see Implementation in ScalarAddNodeOp
/** @} */

/**
 * @name Subtraction
 * @brief Performs \f$ a - b \f$ in the expression graph
 *
 * @{
*/
Expr operator-(Expr a, Expr b);   //!< @see Implementation in MinusNodeOp
Expr operator-(float a, Expr b);  //!< @see Implementation in ScalarAddNodeOp
Expr operator-(Expr a, float b);  //!< @see Implementation in ScalarAddNodeOp
/** @} */

/**
 * @name Multiplication
 * @brief Performs \f$ a * b \f$ in the expression graph
 *
 * @{
*/
Expr operator*(Expr a, Expr b);   //!< @see Implementation in MultNodeOp
Expr operator*(float a, Expr b);  //!< @see Implementation in ScalarMultNodeOp
Expr operator*(Expr a, float b);  //!< @see Implementation in ScalarMultNodeOp
/** @} */

/**
 * @name Division
 * @brief Performs \f$ a / b \f$ in the expression graph
 *
 * @{
*/
Expr operator/(Expr a, Expr b);   //!< @see Implementation in DivNodeOp
Expr operator/(float a, Expr b);  //!< Promotes @p a to Expression<ConstantNode> and uses operator/(Expr a, Expr b).
                                  //!< @todo efficient version of this without ExpressionGraph::constant
Expr operator/(Expr a, float b);  //!< Implementation via \f$ a * \frac{1}{b} \f$.
/** @} */

/** @} */

/**
 * @ingroup graph_ops_mathematical
 * @brief Computes the square root of an expression.
 *
 * Evaluates \f$\sqrt{a + \mathrm{eps}} \f$ element-wise on the expression
 *
 * @param a Expression to square root
 * @param eps Optional positive epsilon to avoid domain errors for small values in @p a
 */
Expr sqrt(Expr a, float eps = 0.f);

/**
 * @ingroup graph_ops_mathematical
 * @brief Computes the square of an expression.
 *
 * Evaluates \f$a^2 \f$ element-wise on the expression
 *
 * @param a Expression to square
 */
Expr square(Expr a);

/**
 * @ingroup graph_ops_mathematical
 * @brief Calculate the element-wise abolute value of an expression.
 *
 * Returns the value of \f$ |a| \f$ element-wise for the expression @p a.
 * @see AbsNodeOp.
 */
Expr abs(Expr a);

// Expr pow(Expr a, Expr b);
// Expr pow(float a, Expr b);
// Expr pow(Expr a, float b);

Expr logaddexp(Expr a, Expr b);

/**
 * @name Element-wise min/max
 * @brief Performs an element-wise min max comparison between expressions
 *
 * @see min, max for axis level operations
 * @see MinimumNodeOp, MaximumNodeOp
 * @todo implement version without ExpressionGraph::constant.
 * @{
*/
/**
 * @brief Computes the element-wise maximum of its inputs.
 */
Expr maximum(Expr a, Expr b);

/**
 * @copybrief maximum
 *
 * Promotes float input to a @ref ExpressionGraph::constant.
 */
Expr maximum(float a, Expr b);

/**
 * @copybrief maximum
 *
 * Promotes float input to a @ref ExpressionGraph::constant.
 */
Expr maximum(Expr a, float b);

/**
 * @brief Computes the element-wise minimum its inputs.
 */
Expr minimum(Expr a, Expr b);

/**
 * @copybrief minimum
 *
 * Promotes float input to a @ref ExpressionGraph::constant.
 */
Expr minimum(float a, Expr b);

/**
 * @copybrief minimum
 *
 * Promotes float input to a @ref ExpressionGraph::constant.
 */
Expr minimum(Expr a, float b);
/** @} */

// Pair of expressions, currently used for topk nodes only
typedef std::tuple<Expr, Expr> Expr2;

// Marian pseudo-operator to access elements of a tuple, just the same as std::get<N>(tuple)
template <int I>
Expr get(Expr2 tuple) { return std::get<I>(tuple); }

// PyTorch-like topk operator, returns a 2-tuple of nodes, first node is top-k values
// second node is indices of these values according to given axis. Order is descending
// by default, outputs are ordered.
Expr2 topk(Expr a, int k, int axis, bool descending = true);

// Convenience operator that maps to topk(a, k=1, axis, descending=true) 
Expr2 argmax(Expr a, int axis);

// Convenience operator that maps to topk(a, k=1, axis, descending=false)
Expr2 argmin(Expr a, int axis);


/**
 * @addtogroup graph_ops_cmp Comparison
 * @ingroup graph_ops
 * @brief Performs comparision operations in the expression graph
 *
 * Uses CmpNodeOp to perform comparison of graph expression e.g. \f$ a < b \f$.
 *
 * @note
 * We cannot overload the relational operators, as they also mean something for Expr itself.
 * @par
 * @note
 * These names follow <a href="https://pytorch.org/docs">PyTorch</a> convention.
 *
 * @{
 */
/**
 * @name Expr-Expr comparisons
 * @{
 */
Expr lt(Expr a, Expr b);  //!< \f$ a < b \f$
Expr eq(Expr a, Expr b);  //!< \f$ a \equiv b \f$
Expr gt(Expr a, Expr b);  //!< \f$ a > b \f$
Expr ge(Expr a, Expr b);  //!< \f$ a \geq b \f$
Expr ne(Expr a, Expr b);  //!< \f$ a \neq b \f$
Expr le(Expr a, Expr b);  //!< \f$ a \leq b \f$
/** @} */

/**
 * @name Float-Expr comparisons
 * Floats are promoted to a @ref ExpressionGraph::constant and use the Expr-Expr methods
 * @{
 */
Expr lt(float a, Expr b);  //!< \f$ a < b \f$
Expr eq(float a, Expr b);  //!< \f$ a \equiv b \f$
Expr gt(float a, Expr b);  //!< \f$ a > b \f$
Expr ge(float a, Expr b);  //!< \f$ a \geq b \f$
Expr ne(float a, Expr b);  //!< \f$ a \neq b \f$
Expr le(float a, Expr b);  //!< \f$ a \leq b \f$

Expr lt(Expr a, float b);  //!< \f$ a < b \f$
Expr eq(Expr a, float b);  //!< \f$ a \equiv b \f$
Expr gt(Expr a, float b);  //!< \f$ a > b \f$
Expr ge(Expr a, float b);  //!< \f$ a \geq b \f$
Expr ne(Expr a, float b);  //!< \f$ a \neq b \f$
Expr le(Expr a, float b);  //!< \f$ a \leq b \f$
/** @} */

/** @} */

Expr dot(Expr a,
         Expr b,
         bool transA = false,
         bool transB = false,
         float scalar = 1.f);

Expr bdot(Expr a,
          Expr b,
          bool transA = false,
          bool transB = false,
          float scalar = 1.f);

Expr affine(Expr a,
            Expr b,
            Expr c,
            bool transA = false,
            bool transB = false,
            float scalar = 1.f);

Expr csr_dot(const Shape& A_shape, Expr Avalues, Expr Aindices, Expr Aoffsets, Expr B, bool transA = false);
Expr dot_csr(Expr A, const Shape& B_shape, Expr B_values, Expr B_indices, Expr B_offsets, bool transB = false);

/**
 * @addtogroup graph_ops_manipulation Manipulation Operations
 * @ingroup graph_ops
 * @brief Operators that manipulate expressions.
 *
 * @{
 */

/**
 * @brief Returns the transpose of an expression.
 *
 * Swaps the last two axes of an expression.
 * @see TransposeNodeOp
 */
Expr transpose(Expr a);

/**
 * @brief Returns the transpose of an expression.
 *
 * Permutes the axes of an expression to resemble @p axes. Axis @c i of the returned
 * expression corresponds to @c axes[i] of the input @p a.
 *
 * @param a Expression to manipulate
 * @param axes Desired permutation of axes
 * @see TransposeNodeOp
 */
Expr transpose(Expr a, const std::vector<int>& axes);

/**
 * @brief Swap two axes of an expression.
 *
 * Swaps two axes of an expression via reshaping, if possible, or transpose.
 *
 * @param x      Expression to manipulate
 * @param axis1  Axis to be swapped
 * @param axis2  Axis to swap with
 *
 * @returns Expression with the axes @p axis1 and @p axis2 interchanged
 * @see reshape() and transpose()
 */
Expr swapAxes(Expr x, int axis1, int axis2);

/**
 * @brief Cast an expression to a specified type.
 *
 * @param a    Expression to cast
 * @param type Desired type
 * @returns    Expression with data cast to @p type
 */
Expr cast(Expr a, Type type = Type::float32);

/**
 * @brief Join a list of expressions along an axis.
 *
 * Concatenates the elements of the expressions in @p concats along the axis @p ax.
 * By default, @p ax operates on the first axis.
 */
Expr concatenate(const std::vector<Expr>& concats, int ax = 0);

/**
 * @brief Repeat elements of an expression.
 *
 * Repeats the elements of @p a along the  @p ax axis @p repeats times.
 * By default, @p ax operates on the first axis.
 * @see concatenate()
 */
Expr repeat(Expr a, size_t repeats, int ax = 0);

/**
 * @brief Reshape expression to a given shape.
 *
 * @param a The expression to be reshaped
 * @param shape The new shape
 * @returns An expression with shape @p shape.
 */
Expr reshape(Expr a, Shape shape);

/**
 * @brief Clip the values in an expression.
 *
 * Clips the values of the Expr @p a to be within the interval \f$ [-c, c] \f$.
 *
 * @param a Expr to clip
 * @param c Threshold to clip at
 *
 * @see ClipNodeOp
 */
Expr clip(Expr a, float c);

/**
 * @brief Clip the gradient in an expression.
 *
 * Clips the gradient of the Expr @p a to be within the interval \f$ [-c, c] \f$
 *
 * @see clip for the equivalent function which clips values
 * @see ClipGradientNodeOp
 */
Expr clipGradient(Expr a, float c);

/**
 * @brief Converts input to an expression with a least one dimension.
 * @see atleast_nd()
 */
Expr atleast_1d(Expr a);

/**
 * @brief Converts input to an expression with a least two dimensions.
 * @see atleast_nd()
 */
Expr atleast_2d(Expr a);

/**
 * @brief Converts input to an expression with a least three dimensions.
 * @see atleast_nd()
 */
Expr atleast_3d(Expr a);

/**
 * @brief Converts input to an expression with a least four dimensions.
 * @see atleast_nd()
 */
Expr atleast_4d(Expr a);

/**
 * @brief Converts input to an expression with a least n-dimension dimensions.
 * @param a Expression
 * @param dims Required number of dimensions
 * @returns An expression with at least n-dimensions
 */
Expr atleast_nd(Expr a, size_t dims);
/** @} */

/**
 * @addtogroup graph_ops_creation Creation Operations
 * @ingroup graph_ops
 * @brief Operators that create expressions.
 *
 * @{
 */

/**
 * @brief Create a constant of with the shape of @p a and initialize with @p init.
 * @todo add a && version, to avoid a ref count. NodeInitializers are typically temps.
 * and/or make this a template on init
 */
static inline Expr constant_like(Expr a, const Ptr<inits::NodeInitializer>& init) {
  return a->graph()->constant(a->shape(), init, a->value_type());
}

/**
 * @brief Convenience function to initialize from a vector.
 */
template<typename ElementType>
Expr constant_like(Expr a, const std::vector<ElementType>& v) { return constant_like(a, inits::fromVector(std::move(v))); }

/**
 * @brief Convenience function to initialize from a vector.
 */
template<typename ElementType>
Expr constant_like(Expr a, std::vector<ElementType>&& v) { return constant_like(a, inits::fromVector(v)); }

/** @} */

/**
 * @addtogroup graph_ops_manipulation
 * @{
 */

/**
 * @brief Flattens an expression to one dimension.
 * @see ReshapeNodeOp
 */
Expr flatten(Expr a);

/**
 * @brief Flattens an expression to two-dimensions preserving the last dimension.
 * @see ReshapeNodeOp
 */
Expr flatten_2d(Expr a);

/** @} */

Expr stopGradient(Expr a);

Expr gather(Expr a, int axis, Expr indices);

#if 0
 // reverse operation to gather. a is expression into with values from b are inserted and positions indices along axis.
 // with broadcasting

 auto knn = get<0>(KNN->apply(query, k)); // [beam, time, batch, k]

 auto W = reshape(gather(Wt_, -2, flatten(knn)), {beam * time * batch, k, dim});
 auto b = reshape(gather(b_,  -1, flatten(knn)), {beam * time * batch, 1, k });
 query       = reshape(query, {beam * time * batch, 1, dim});
 auto logits = bdot(query, W, false, true); // [beam * time * batch, 1, k]
 logits      = reshape(logits + b, {beam, time, batch, k}); // @TODO: add baffine node

 auto shape = indices.shape();
 shape.set(-1, 32000);
 auto output = grep->constant(shape, inits::lowest(), logits->value_type());
 output = scatter(output, -1, indices, logits);

 // auto a = graph->constant({2,2,5,32000}, inits::fromValue(minimal))
 // scatter(a, -1, indices, values)
 // PyTorch does for out-of-place scatter: out = a.scatter(-1, indices, values)
Expr scatter(Expr a, int axis, Expr indices, Expr b);

#endif

// Warning: Don't try to pass a scalar literal 0 as indices; it will compile but pass nullptr...
Expr index_select(Expr a, int axis, Expr indices);

// convenience wrappers for index_select()
Expr index_select(Expr a, int axis, const std::vector<IndexType>& indices);
static inline Expr rows(Expr a, Expr indices) {
  return index_select(a, 0, indices);
}
static inline Expr rows(Expr a, const std::vector<IndexType>& indexVector) {
  return index_select(a, 0, indexVector);
}
static inline Expr cols(Expr a, Expr indices) {
  return index_select(a, -1, indices);
}
static inline Expr cols(Expr a, const std::vector<IndexType>& indexVector) {
  return index_select(a, -1, indexVector);
}

Expr slice(Expr a, int axis, Slice slice);

// convenience wrappers for slice()
static inline Expr slice(Expr a, int axis, int index) { // single index  @NOTE: This was formerlly called step()
  return slice(a, axis, Slice(index));
}

static inline Expr narrow(Expr a, int axis, size_t start, size_t length) { // PyTorch name
  return slice(a, axis, Slice((int)start, (int)(start + length)));
}

/*********************************************************/

Expr sum(Expr a, int ax = 0);
Expr mean(Expr a, int ax = 0);
Expr std(Expr a, int ax);
Expr var(Expr a, int ax);
Expr max(Expr a, int ax);
Expr min(Expr a, int ax);
Expr prod(Expr a, int ax);
Expr logsumexp(Expr a, int ax);

Expr softmax(Expr x, int axis = -1);

// @TODO: maybe get rid of this entirely to not obfuscate, what's going on inside.
// @TODO: switch to log-masking everywhere?
Expr softmax(Expr a, Expr zeroOneMask, int axis = -1);

Expr logsoftmax(Expr a);

Expr cross_entropy(Expr a, Expr b, float labelSmoothingAlpha = 0.f, Type outputType = Type::float32);

Expr unlikelihood(Expr a, Expr b);

Expr scalar_product(Expr a, Expr b, int ax = 0);

Expr weighted_average(Expr in, Expr weights, int ax = 0);


Expr layerNorm(Expr x, Expr gamma, Expr beta = nullptr, float eps = 1e-9);

Expr highway(Expr y, Expr x, Expr t);
Expr highway(const std::string prefix, Expr x);

static inline Expr dropout(Expr x, Expr mask) {
  if (mask)
    return x * mask;
  else
    return x;
}

static inline Expr dropout(Expr x, float dropProb, Shape shape) {
  if(dropProb == 0)
    return x;
  auto graph = x->graph();
  auto mask = graph->dropoutMask(dropProb, shape);
  return dropout(x, mask);
}

static inline Expr dropout(Expr x, float dropProb) {
  if(dropProb == 0)
    return x;
  return dropout(x, dropProb, x->shape());
}

Expr shift(Expr, Shape, float padValue = 0);

Expr convert2cudnnFormat(Expr x);

Expr convertFromcudnnFormat(Expr x);

Expr avg_pooling(Expr x,
                 int height,
                 int width,
                 int padHeight = 0,
                 int padWidth = 0,
                 int strideHeight = 1,
                 int strideWidth = 1);

Expr max_pooling(Expr x,
                 int height,
                 int width,
                 int padHeight = 0,
                 int padWidth = 0,
                 int strideHeight = 1,
                 int strideWidth = 1);

Expr pooling_with_masking(Expr x, Expr mask, int width, bool isEven = false);

/** @} */
}  // namespace marian
