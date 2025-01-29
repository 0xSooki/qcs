# Circuit simulator

<img width="694" alt="qcs" src="https://github.com/user-attachments/assets/3d586f8c-3536-4fcb-b944-519d0fc53a62" />


## Basic Features (Minimum Requirements)
The following are the essential features needed to pass the project. They are required but do not provide extra credit.


1. **Basic Quantum Components:** Implement core quantum gates such as Pauli-X (NOT), Pauli-Y, Pauli-Z, Hadamard (H), and CNOT gates.
2. **Graphical User Interface (GUI):** Develop a graphical interface for users to design and simulate quantum circuits. The interface should allow users to:
    - Add, move, connect, and remove quantum gates and qubits.
    - Visualize the evolution of quantum states.
3. **Circuit Persistence:** Allow users to save and load quantum circuits to and from files, preserving their structure and configurations.
4. **Quantum State Calculations:** Compute and display the final state vector of the quantum circuit after the gates are applied.
5. **Ready-made Quantum Circuits:** Include several pre-built circuits (e.g., Bell state generation, quantum teleportation) to demonstrate the program’s functionality.

## Additional Features (Optional for Higher Grades)
These features are worth additional points (usually two points each) and can improve your grade. Confirm with your teaching assistant if you have ideas for additional features not listed below.

1. **Quantum Measurement:** Implement measurement functionality that collapses quantum states to either |0⟩ or |1⟩, showing the probabilities of each outcome.
2. **Parameterized Quantum Gates:** Add parameterized gates like rotation gates (e.g., RX, RY, RZ) that accept angles as input.
3. **Quantum Noise Models:** Simulate realistic quantum noise models, such as depolarizing noise or phase damping, which can be toggled on or off for error simulation.
4. **Entanglement Visualization:** Show visual indications of entanglement between qubits, helping users understand quantum correlations.
5. **Quantum Fourier Transform (QFT):** Implement and demonstrate the Quantum Fourier Transform, displaying its impact on multi-qubit systems.
6. **Circuit Optimization:** Implement basic optimization features that minimize the number of gates or simplify operations within the circuit.
7. **Time and Frequency Domain Analysis:** Visualize the effects of quantum gates over time or across frequency domains, similar to classical simulators' time and frequency graphs (adapted for quantum systems).

## Advanced Features (Challenging for Extra Credit)
For a more challenging experience and extra points, you can implement one or more of these advanced features.

1. **Quantum Algorithm Simulation:** Implement basic quantum algorithms like Grover’s search or Shor’s algorithm, simulating their steps and outcomes.
2. **Quantum Circuit Compilation:** Add the capability to compile quantum circuits to hardware-specific gate sets (e.g., IBM Q or Rigetti’s gate sets).
3. **Quantum Error Correction:** Implement simple quantum error correction codes, such as the three-qubit bit flip code or the Shor code, and simulate their operation.
4. **Tensor Network Simulation:** Introduce a tensor network-based simulation approach for efficient simulation of large quantum circuits with many qubits.
5. **Multi-qubit Gate Decomposition:** Allow for the decomposition of multi-qubit gates (e.g., Toffoli or Fredkin) into universal one- and two-qubit gates.

# Group
- bence.sooki-toth@aalto.fi
- ha.k.do@aalto.fi
- henna.makiluoma@aalto.fi
- emma.erdei@aalto.fi
- matti.viljamaa@aalto.fi

# Repository organization
Your project implementation should follow the skelaton organization in this repository.
See readme.md files in each folder.

# Project Implementation 
You must use git repository for the work on the project, making frequent enough commits so 
that the project group (and course staff) can follow the progress.

The completed project work will be demonstrated to the group's advisor at a demo session. 
The final demonstrations are arranged on week 50. After the final demonstrations project group 
evaluates another project, and self-evaluates own project. In addition, project members will 
give a confidential individual assessment of each group member

The course staff should be able to easily compile the project work using makefile and related 
instructions provided in the git repository. The final output should be in the **master branch** of the git repository.

# Working practices
Each project group is assigned an advisor from the project teaching personnel. 
There will be a dedicated Teams channel for each project topic to facilitate discussion between 
the groups in the same topic and the advisor. 

**The group should meet weekly.** The weekly meeting does not need to be long if there are no special issues 
to discuss, and can be taken remotely as voice/video chat on the group Teams channel (or Zoom or other similar tool), 
preferably at a regular weekly time. In the meeting the group updates:

- What each member has done during the week
- Are there challenges or problems? Discuss the possible solutions
- Plan for the next week for everyone
- Deviations and changes to the project plan, if any
- After the meetings, the meeting notes will be committed to the project repository in the `Meeting-notes.md` file. 
    * The commits within the week should have some commit messages referring to the meeting notes so 
      that the project advisor can follow the progress.  
    * **The meeting notes should be in English.**

> Everyone may not be able to participate to all meetings, but at least a couple of members should be present in each meeting. 
> Regular absence from meetings will affect in individual evaluation.

# Source code documentation
It is strongly recommended to use Doxygen to document your source code.
Please go over the *Project Guidelines* for details.

# TODOs (Date)
You can create a list of TODOs in this file.
The recommended format is:
- Complete class implementation **foo**. Assigned to \<Member 1\>
- Test ...
