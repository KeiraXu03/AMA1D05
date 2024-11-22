**The Cauchy-Schwarz Inequality**
$$\left( \sum_{k=1}^n a_k b_k \right)^2 \leq \left( \sum_{k=1}^n a_k^2 \right) \left( \sum_{k=1}^n b_k^2 \right)$$

  $$
R(s, a) = \begin{cases} 
1 & \text{if action = label} \\
0 & \text{otherwise}
\end{cases}
$$
# Different Machine Learning Methods on Classification Problems

In this project, we will explore various machine learning methodologies including supervised learning, unsupervised learning (SVM), and reinforcement learning (such as Deep Q-Learning and Actor-Critic algorithms) applied to the NSL-KDD dataset for classification tasks, and investigate their advantages and disadvantages.

The NSL-KDD dataset consists of network traffic data collected from a simulated computer network environment, featuring both normal and various types of attack activities. This diversity of intrusion scenarios makes the dataset an excellent resource for evaluating the performance of intrusion detection systems.

For this study, we utilized a pre-processed and normalized version of the NSL-KDD dataset. The dataset contains a total of 42 features, with the first 41 used as states for the DQN model and the 42nd feature serving as the label for computing the reward vector.

![Table 1: List of features on NSL-KDD dataset](description.png "Optional Title")

Overall, these methods achieve a significant number of True Positives (TP) and True Negatives (TN), and a relatively small number of False Positives (FP), but they tend to have a high number of False Negatives (FN). Current tests are conducted with epochs ranging between 500-1000. Potential improvements could include increasing the number of hidden network layers, as well as the depth of those layers, and possibly extending the number of epochs, given the NSL-KDD dataset includes over 40 attributes.

Generally, the results across the models are comparable, with accuracies and F1-scores around 0.78-0.82, recall rates at 0.68-0.72, and precision ranging from 0.93-0.95. These results indicate a high correctness rate among positive predictions by the models, though they still miss identifying some true positives, classifying them as negatives instead. Adjustments as mentioned above might be required to address these issues.

In terms of performance with the same parameters (e.g., hidden layer=100, epoch=1000, learning rate=0.1), the training results rank as follows: SVM > DQN ≥ Actor-Critic ≥ Supervised Learning. Increasing the epochs tends to improve model performance to a certain extent, but limitations remain.

1. **Unsupervised Learning Method**
   We employed the simple SVM method. The results on the test data are shown below:
   ![Table 2: Confusion Matrix for SVM](result_SVM/20241118_215457/confusion_matrix.png "Optional Title")

2. **Supervised Learning Method**
   We used logistic regression with the SGD optimizer and CrossEntropyLoss.
   ![Table 3: Confusion Matrix for SL](result_SL/20241119_110824/confusion_matrix.png "Optional Title")
   ![Table 4: Loss function for SL](result_SL/20241119_110824/loss_history.png "Optional Title")

3. **Reinforcement Learning Methods**
   - **State**: The first 41 features of the NSL-KDD dataset, providing a high dimensionality.
   - **Actions**: Two options are available. The actions represent two possibilities: action 1 indicating an anomaly, and action 0 denoting normal behavior. The actions are selected by the reinforcement learning algorithm (random selection, maximizing Q-table, etc.).
     ![Table 5: Explanation for Action](label.png "Optional Title")
   - **Reward**: Compared with the last feature of the NSL-KDD dataset. If the action matches the corresponding label value, the agent receives a reward of 1; otherwise, the reward is 0.
     
     $$
     R(s, a) = \begin{cases} 
     1 & \text{if action = label} \\
     0 & \text{otherwise}
     \end{cases}
     $$

   - **State Transition**:
     There is no strict state transition equation; training proceeds sequentially from top to bottom of the database (i.e., if St is the i-th row of data, then St+1 is the i+1-th row).

### Deep Q-Learning (DQN) and Actor-Critic Methods Explained

#### a. Deep Q-Learning (DQN)

Deep Q-Learning integrates the classic Q-learning technique with deep neural networks, enabling the handling of high-dimensional state spaces.

##### Key Components
- **Reward Function**: This function defines the rewards given to the agent based on its actions and the resulting state changes.
- **Loss Function**: Typically, DQN uses the mean squared error of the difference between the current predicted Q-values and the target Q-values.
- **Network Structure**: Consists of a deep neural network that approximates the Q-value function, often structured with multiple hidden layers.

##### Formulas and Functions
- **Q-value Update Rule**:
  
   $$
   Q(s_t, a_t) \leftarrow Q(s_t, a_t) + \alpha \left( r_{t+1} + \gamma \max_a Q(s_{t+1}, a) - Q(s_t, a_t) \right)
   $$
  
- **Action Selection**: In DQN, action selection is managed by an ε-greedy policy, which mixes exploration and exploitation to improve learning. The exploration rate is dynamically adjusted as follows:
  $$
  \[
  \text{exploration} = \text{decay\_rate}^{(\text{epoch} / 5)}
  \]
  $$
  This lets the exploration rate decrease as the number of epochs increases, leading to a better balance of exploration and exploitation.
  
  Actions are then chosen based on:
  $$
  \[
  a_t = \begin{cases} 
  \text{random action} & \text{with probability } \epsilon \\
  \arg\max_a Q(s_t, a) & \text{with probability } 1-\epsilon
  \end{cases}
  \]
  $$
- **Loss Function**:
  $$
  \[
  \text{Loss} = \left(r + \gamma \max_{a'}Q(s', a') - Q(s, a)\right)^2
  \]
  $$

#### b. Actor-Critic

Actor-Critic methods use two models: one to generate the policy (actor) and another to evaluate actions (critic).

##### Key Components
- **Reward Function**: Rewards are given based on the results of actions, similar to DQN.
- **Loss Functions**:
  - **Actor Loss**: Optimizes the policy network using policy gradients.
  - **Critic Loss**: Updates the value network using the temporal difference (TD) error.
- **Network Structures**:
  - **Actor Network**: Outputs a probability distribution over possible actions.
  - **Critic Network**: Outputs a value estimating the expected return from the current state.

##### Formulas and Functions
- **Action Function (Actor)**:
  $$
  \[
  \pi(a|s, \theta) \text{, where }\theta \text{ are the parameters of the actor network}
  \]
  $$
- **Value Function (Critic)**:
  $$
  \[
  V^\pi(s) \text{, approximated by the critic network}
  \]
  $$
- **Actor Loss**:
  $$
  \[
  L(\theta) = -\log(\pi(a|s, \theta)) \cdot A(s, a)
  \]
  $$
  Where $\( A(s, a) \)$ is the advantage function, computed as $\( r + \gamma V(s') - V(s) \)$.
- **Critic Loss**:
  $
  L(w) = \left(r + \gamma V(s', w) - V(s, w)\right)^2
  $
  Where $\( w \)$ are the parameters of the critic network.

These methods provide robust frameworks for solving complex reinforcement learning problems, particularly in environments with large or continuous state and action spaces. The results with different epochs are shown in the attached folder.
